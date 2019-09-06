#include "Action.h"

#include "util/Exception.h"

namespace map {

std::string to_string(Action enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(Action::NONE);
        CASE_ENUM_TO_STRING(Action::PLAYER);
        CASE_ENUM_TO_STRING(Action::ENEMY_NORTH);
        CASE_ENUM_TO_STRING(Action::ENEMY_EAST);
        CASE_ENUM_TO_STRING(Action::ENEMY_SOUTH);
        CASE_ENUM_TO_STRING(Action::ENEMY_WEST);
        CASE_ENUM_TO_STRING(Action::BANG);
        CASE_ENUM_TO_STRING(Action::STONE_1);
        CASE_ENUM_TO_STRING(Action::STONE_2);
        CASE_ENUM_TO_STRING(Action::SMOKE);
        CASE_ENUM_TO_STRING(Action::FUEL);
        CASE_ENUM_TO_STRING(Action::FUEL_L);
        CASE_ENUM_TO_STRING(Action::FUEL_S);
        case Action::LAST:
            break;
    }
    throw util::Exception("to_string(EAction) - invalid argument", util::from_Enum<int>(enum_value));
}
}
