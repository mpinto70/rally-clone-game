
#include "CMapIO.h"
#include "util/CException.h"

#include <cstring>
#include <fstream>
#include <iostream>

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

    const auto qttyTiles = width * height;
    std::vector<ETile> tiles;
    tiles.reserve(qttyTiles);
    tile_t t;
    char * pt = (char *) &t;
    for (size_t i = 0; i < qttyTiles; ++i) {
        is.read(pt, sizeof(tile_t));
        if (not is || is.gcount() != sizeof(tile_t)) {
            throw util::CException("CMapReader::read(is) - could not read tile " + std::to_string(i), i);
        }
        tiles.push_back(to_ETile(t));
        is.read(pt, sizeof(tile_t)); // skipping action
        if (not is || is.gcount() != sizeof(tile_t)) {
            throw util::CException("CMapReader::read(is) - could not skip action " + std::to_string(i), i);
        }
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
        throw util::CException("CMapReader::write(os) - could not write width", width);
    }

    const auto height = map.height();
    memcpy(buffer.data(), &height, sizeof(map_dimension_t));
    os.write(buffer.data(), buffer.size());
    if (not os) {
        throw util::CException("CMapReader::write(os) - could not write height", height);
    }

    const auto qttyTiles = width * height;
    tile_t t;
    char * pt = (char *) &t;
    for (size_t i = 0; i < qttyTiles; ++i) {
        t = from_ETile<tile_t>(map.tiles()[i]);
        os.write(pt, sizeof(tile_t));
        if (not os) {
            throw util::CException("CMapReader::write(os) - could not write tile " + std::to_string(i), i);
        }
        os.write(pt, sizeof(tile_t)); // skipping action
        if (not os) {
            throw util::CException("CMapReader::read(is) - could not write action " + std::to_string(i), i);
        }
    }
}

}
