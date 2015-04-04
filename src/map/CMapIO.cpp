
#include "CMapIO.h"
#include "util/CException.h"

namespace map {
class SafeFILE {
    public:
        SafeFILE(const std::string & fileName,
                 const std::string & mode) {
            fp_ = fopen(fileName.c_str(), mode.c_str());
            if (fp_ == nullptr) {
                throw util::CException("CMapReader::readMap - could not open file " + fileName, 0);
            }
        }

        ~SafeFILE() {
            fclose(fp_);
        }

        FILE * get() const { return fp_; }
    private:
        FILE * fp_;
};

typedef std::uint32_t map_dimension_t;

CMap CMapIO::read(const std::string & fileName) {
    SafeFILE fp(fileName, "rb");
    map_dimension_t width, height;
    if (fread(&width, sizeof(map_dimension_t), 1, fp.get()) != 1) {
        throw util::CException("CMapReader::readMap - there was no space in " + fileName + " to read width", width);
    }
    if (fread(&height, sizeof(map_dimension_t), 1, fp.get()) != 1) {
        throw util::CException("CMapReader::readMap - there was no space in " + fileName + " to read height", height);
    }

    std::vector<tile_t> tiles_t(width * height, 0);
    if (fread(tiles_t.data(), sizeof(tile_t), tiles_t.size(), fp.get()) != tiles_t.size()) {
        throw util::CException("CMapReader::readMap - there was no space in " + fileName + " to read map data", tiles_t.size());
    }

    std::vector<ETile> tiles;
    tiles.reserve(tiles_t.size());

    for (auto t : tiles_t) {
        tiles.push_back(util::to_Enum<ETile>(t));
    }
    return CMap(width, height, tiles);
}

void CMapIO::write(const std::string & fileName,
                   const CMap& map) {
    SafeFILE fp(fileName, "wb");
    const map_dimension_t width = map.width();
    const map_dimension_t height = map.height();
    if (fwrite(&width, sizeof(map_dimension_t), 1, fp.get()) != 1) {
        throw util::CException("CMapReader::writeMap - could not write width to " + fileName, width);
    }
    if (fwrite(&height, sizeof(map_dimension_t), 1, fp.get()) != 1) {
        throw util::CException("CMapReader::writeMap - could not write height to " + fileName, height);
    }
    std::vector<tile_t> tiles;
    tiles.reserve(map.tiles().size());
    for (const auto tile : map.tiles()) {
        tiles.push_back(static_cast<tile_t>(tile));
    }
    if (fwrite(tiles.data(), tiles.size(), sizeof(tile_t), fp.get()) != 1) {
        throw util::CException("CMapReader::writeMap - could not write map to " + fileName, tiles.size());
    }
}

}
