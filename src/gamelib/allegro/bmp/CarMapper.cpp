#include "CarMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

CarMapper createCarMapper(const BITMAP_PTR& fullImage, CarSource type) {
    constexpr unsigned CAR_TILE_SIZE = 48;

    const auto y0 = util::from_Enum<unsigned>(type) * CAR_TILE_SIZE;
    const auto number_of_cars = util::from_Enum<unsigned>(car::Orientation::LAST);
    return CarMapper(fullImage, CAR_TILE_SIZE, CAR_TILE_SIZE, 0, y0, number_of_cars, 1);
}

std::string to_string(CarSource enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(CarSource::PLAYER_1);
        CASE_ENUM_TO_STRING(CarSource::ENEMY_1);
        CASE_ENUM_TO_STRING(CarSource::PLAYER_2);
        CASE_ENUM_TO_STRING(CarSource::ENEMY_2);
        case CarSource::LAST:
            break;
    }
    throw util::Exception("to_string(CarSource) - invalid argument", util::from_Enum<int>(enum_value));
}

}
}
}
