#pragma once

#include "gamelib/allegro/bmp/CBmpMapper.h"
#include "map/ETileType.h"

namespace gamelib {
namespace allegro {
namespace bmp {

typedef CBmpMapper<map::ETileType> CTileMapper;
}
}
}
