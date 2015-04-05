
#include "CMapIO.h"
#include "util/CException.h"

#include <cstring>
#include <fstream>

namespace map {

typedef std::uint32_t map_dimension_t;

CMap CMapIO::read(const std::string & fileName) {
    std::ifstream is(fileName, std::ios_base::in | std::ios_base::binary);
    return read(is);
}

void CMapIO::write(const std::string & fileName,
                   const CMap& map) {
    std::ofstream os(fileName, std::ios_base::out | std::ios_base::binary);
    write(os, map);
}

CMap CMapIO::read(std::istream & is) {
    map_dimension_t width, height;

    std::vector<char> buffer(sizeof(map_dimension_t), '\0');

    is.read(buffer.data(), buffer.size());

    if (not is || is.gcount() != sizeof(map_dimension_t)) {
        throw util::CException("CMapReader::read(is) - could not read width", 1);
    }

    memcpy(&width, buffer.data(), sizeof(map_dimension_t));

    is.read(buffer.data(), buffer.size());

    if (not is || is.gcount() != sizeof(map_dimension_t)) {
        throw util::CException("CMapReader::read(is) - could not read height", 2);
    }

    memcpy(&height, buffer.data(), sizeof(map_dimension_t));

    buffer = std::vector<char>(width * height * sizeof(tile_t), 0);

    is.read(buffer.data(), buffer.size());

    if (not is || is.gcount() != (std::streamsize)(width * height * sizeof(tile_t))) {
        throw util::CException("CMapReader::read(is) - could not read map", 3);
    }

    std::vector<tile_t> tiles_t(width * height, 0);
    memcpy(tiles_t.data(), buffer.data(), buffer.size());

    std::vector<ETile> tiles;
    tiles.reserve(tiles_t.size());

    for (auto t : tiles_t) {
        tiles.push_back(util::to_Enum<ETile>(t));
    }
    return CMap(width, height, tiles);
}

void CMapIO::write(std::ostream & os,
                   const CMap & map) {
    std::vector<char> buffer(sizeof(map_dimension_t), 0);

    const auto width = map.width();
    memcpy(buffer.data(), &width, sizeof(map_dimension_t));
    os.write(buffer.data(), buffer.size());
    if (not os) {
        throw util::CException("CMapReader::write(is) - could not write width", width);
    }

    const auto height = map.height();
    memcpy(buffer.data(), &height, sizeof(map_dimension_t));
    os.write(buffer.data(), buffer.size());
    if (not os) {
        throw util::CException("CMapReader::write(is) - could not write height", height);
    }

    buffer = std::vector<char>(width * height * sizeof(tile_t), 0);
    const auto & tiles = map.tiles();
    std::vector<tile_t> tiles_t;
    tiles_t.reserve(width * height);
    for (const auto tile : tiles) {
        tiles_t.push_back(static_cast<tile_t>(tile));
    }
    memcpy(buffer.data(), tiles_t.data(), buffer.size());
    os.write(buffer.data(), buffer.size());
    if (not os) {
        throw util::CException("CMapReader::write(is) - could not write data", height);
    }
}

}
