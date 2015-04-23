
#include "CMapIO.h"
#include "util/CException.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace map {

CMap CMapIO::read(const std::string & fileName) {
    std::ifstream is(fileName, std::ios_base::in | std::ios_base::binary);
    return read(is);
}

void CMapIO::write(const std::string & fileName,
                   const CMap& map) {
    std::ofstream os(fileName, std::ios_base::out | std::ios_base::binary);
    write(os, map);
}

template <typename T>
static T readField(std::istream & is,
                   const std::string & fieldName) {
    T t;
    char * buffer = reinterpret_cast<char *>(&t);
    is.read(buffer, sizeof(T));
    if (not is || is.gcount() != sizeof(T)) {
        throw util::CException("CMapReader::read(is) - could not read " + fieldName, 1);
    }
    return t;
}

CMap CMapIO::read(std::istream & is) {
    const auto width = readField<map_dimension_t>(is, "width");
    const auto height = readField<map_dimension_t>(is, "height");
    const auto parts = readField<map_dimension_t>(is, "parts");

    const auto qttyTiles = width * height;
    std::vector<CTile> tiles;
    tiles.reserve(qttyTiles);
    for (size_t i = 0; i < qttyTiles; ++i) {
        const auto t = readField<tile_type_t>(is, "tile");
        if (t >= from_ETile<tile_type_t>(ETileType::LAST)) {
            throw util::CException("CMapReader::read(is) - invalid tile " + std::to_string(t) + " read " + std::to_string(i), i);
        }

        const auto a = readField<action_t>(is, "action");
        if (a >= from_EAction<action_t>(EAction::LAST)) {
            throw util::CException("CMapReader::read(is) - invalid action " + std::to_string(a) + " read " + std::to_string(i), i);
        }
        tiles.push_back(CTile(to_ETile(t), to_EAction(a)));
    }
    return CMap(width, height, parts, tiles);
}

template <typename T>
static void writeField(std::ostream & os,
                       const T t,
                       const std::string & fieldName) {
    const char * buffer = reinterpret_cast<const char *>(&t);
    os.write(buffer, sizeof(T));
    if (not os) {
        throw util::CException("CMapReader::write(os) - could not write " + fieldName, 1);
    }
}

void CMapIO::write(std::ostream & os,
                   const CMap & map) {

    writeField(os, map.width(), "width");
    writeField(os, map.height(), "height");
    writeField(os, map.parts(), "parts");
    const auto qttyTiles = map.width() * map.height();
    for (size_t i = 0; i < qttyTiles; ++i) {
        const auto t = from_ETile<tile_type_t>(map.tiles()[i].type());
        const auto a = from_EAction<action_t>(map.tiles()[i].action());
        writeField(os, t, "tile");
        writeField(os, a, "action");
    }
}

}
