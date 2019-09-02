#include "CarMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

CarMapper createCarMapper(const std::string& file_name, ECarType type) {
    const int y0 = util::from_Enum<int>(type) * 32;
    return CarMapper(file_name, 32, 32, 0, y0, 12, 1);
}

std::string to_string(ECarType enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(ECarType::PLAYER_1);
        CASE_ENUM_TO_STRING(ECarType::ENEMY_1);
        CASE_ENUM_TO_STRING(ECarType::PLAYER_2);
        CASE_ENUM_TO_STRING(ECarType::ENEMY_2);
        case ECarType::LAST:
            break;
    }
    throw util::Exception("to_string(ECarType) - invalid argument", util::from_Enum<int>(enum_value));
}

}
}
}
