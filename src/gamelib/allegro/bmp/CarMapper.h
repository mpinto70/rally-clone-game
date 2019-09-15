#pragma once

#include "car/Orientation.h"
#include "gamelib/allegro/bmp/SpriteMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using CarMapper = SpriteMapper<car::Orientation>;

enum class CarSource {
    PLAYER_1 = 0,
    ENEMY_1 = 1,
    PLAYER_2 = 2,
    ENEMY_2 = 3,
    LAST,
    FIRST = PLAYER_1
};

std::string to_string(CarSource);

CarMapper createCarMapper(ALLEGRO_BITMAP& fullImage, CarSource);

}
}
}
