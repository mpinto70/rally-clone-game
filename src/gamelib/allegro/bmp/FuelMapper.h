#pragma once

#include "fuel/Fuel.h"
#include "gamelib/allegro/bmp/SpriteMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using FuelMapper = SpriteMapper<fuel::Type>;

FuelMapper createFuelMapper(const std::string& file_name);

}
}
}
