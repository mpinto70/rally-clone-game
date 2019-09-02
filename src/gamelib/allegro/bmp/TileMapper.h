#pragma once

#include "gamelib/allegro/bmp/SpriteMapper.h"
#include "map/TileType.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using TileMapper = SpriteMapper<map::TileType>;

enum class TileSource {
    GREEN,
    PINK,
    BROWN,
    BLUE,
    GRAY,
    ORANGE,
    LIGHT_GRAY,
    LIGHT_GREEN,
    LAST,
    FIRST = GREEN
};

std::string to_string(TileSource);

TileMapper createTileMapper(const std::string& file_name, TileSource);
}
}
}
