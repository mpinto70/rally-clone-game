#include "CarMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

CarMapper createCarMapper(const std::string& file_name, CarSource type) {
    const auto y0 = util::from_Enum<unsigned>(type) * 32;
    const auto number_of_cars = util::from_Enum<unsigned>(car::Orientation::LAST);
    return CarMapper(file_name, 32, 32, 0, y0, number_of_cars, 1);
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
