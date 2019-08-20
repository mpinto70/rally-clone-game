#include "MapIO.h"

#include "util/Exception.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace map {

Map MapIO::read(const std::string& fileName) {
    std::ifstream is(fileName, std::ios_base::in | std::ios_base::binary);
    return read(is);
}

void MapIO::write(const std::string& fileName, const Map& map) {
    std::ofstream os(fileName, std::ios_base::out | std::ios_base::binary);
    write(os, map);
}

template <typename T>
static T readField(std::istream& is,
      const std::string& fieldName) {
    T t;
    char* buffer = reinterpret_cast<char*>(&t);
    is.read(buffer, sizeof(T));
    if (not is || is.gcount() != sizeof(T)) {
        throw util::Exception("MapReader::read(is) - could not read " + fieldName, 1);
    }
    return t;
}

Map MapIO::read(std::istream& is) {
    const auto width = readField<map_dimension_t>(is, "width");
    const auto height = readField<map_dimension_t>(is, "height");

    const auto qttyTiles = width * height;
    std::vector<Tile> tiles;
    tiles.reserve(qttyTiles);
    for (size_t i = 0; i < qttyTiles; ++i) {
        const auto t = readField<tile_type_t>(is, "tile");
        if (t >= from_ETileType<tile_type_t>(TileType::LAST)) {
            throw util::Exception("MapReader::read(is) - invalid tile " + std::to_string(t) + " read " + std::to_string(i), i);
        }

        const auto a = readField<action_t>(is, "action");
        if (a >= from_EAction<action_t>(Action::LAST)) {
            throw util::Exception("MapReader::read(is) - invalid action " + std::to_string(a) + " read " + std::to_string(i), i);
        }
        tiles.emplace_back(to_ETileType(t), to_EAction(a));
    }
    return Map(width, height, tiles);
}

template <typename T>
static void writeField(std::ostream& os,
      const T t,
      const std::string& fieldName) {
    const char* buffer = reinterpret_cast<const char*>(&t);
    os.write(buffer, sizeof(T));
    if (not os) {
        throw util::Exception("MapReader::write(os) - could not write " + fieldName, 1);
    }
}

void MapIO::write(std::ostream& os,
      const Map& map) {
    writeField(os, map.width(), "width");
    writeField(os, map.height(), "height");
    const auto qttyTiles = map.width() * map.height();
    for (size_t i = 0; i < qttyTiles; ++i) {
        const auto t = from_ETileType<tile_type_t>(map.tiles()[i].type());
        const auto a = from_EAction<action_t>(map.tiles()[i].action());
        writeField(os, t, "tile");
        writeField(os, a, "action");
    }
}
}
