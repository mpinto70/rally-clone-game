#pragma once

#include "car/Orientation.h"
#include "gamelib/allegro/bmp/BmpMapper.h"
#include "gamelib/allegro/bmp/SpriteMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using CarMapper = BmpMapper<car::Orientation>;
using CarSpriteMapper = SpriteMapper<car::Orientation>;
}
}
}
