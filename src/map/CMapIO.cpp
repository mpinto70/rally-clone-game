
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
    std::vector<CTile> tiles;
    tiles.reserve(qttyTiles);
    tile_type_t t;
    action_t a;
    char * pt = (char *) &t;
    char * pa = (char *) &a;
    for (size_t i = 0; i < qttyTiles; ++i) {
        is.read(pt, sizeof(tile_type_t));
        if (not is || is.gcount() != sizeof(tile_type_t)) {
            throw util::CException("CMapReader::read(is) - could not read tile " + std::to_string(i), i);
        }
        if (t >= from_ETile<tile_type_t>(ETileType::LAST)) {
            throw util::CException("CMapReader::read(is) - invalid tile " + std::to_string(t) + " read " + std::to_string(i), i);
        }

        is.read(pa, sizeof(action_t));
        if (not is || is.gcount() != sizeof(tile_type_t)) {
            throw util::CException("CMapReader::read(is) - could not skip action " + std::to_string(i), i);
        }
        if (a >= from_EAction<action_t>(EAction::LAST)) {
            throw util::CException("CMapReader::read(is) - invalid action " + std::to_string(a) + " read " + std::to_string(i), i);
        }
        tiles.push_back(CTile(to_ETile(t), to_EAction(a)));
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
    tile_type_t t;
    action_t a;
    char * pt = (char *) &t;
    char * pa = (char *) &a;
    for (size_t i = 0; i < qttyTiles; ++i) {
        t = from_ETile<tile_type_t>(map.tiles()[i].type());
        os.write(pt, sizeof(tile_type_t));
        if (not os) {
            throw util::CException("CMapReader::write(os) - could not write tile " + std::to_string(i), i);
        }
        a = from_EAction<action_t>(map.tiles()[i].action());
        os.write(pa, sizeof(action_t));
        if (not os) {
            throw util::CException("CMapReader::read(is) - could not write action " + std::to_string(i), i);
        }
    }
}

}
