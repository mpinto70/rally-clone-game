#pragma once

#include "gamelib/allegro/bmp/BmpMapper.h"
#include "map/TileType.h"

namespace gamelib {
namespace allegro {
namespace bmp {

typedef BmpMapper<map::TileType> TileMapper;
}
}
}
