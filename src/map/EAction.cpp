
#include "EAction.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(EAction enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(EAction::NONE);
        CASE_ENUM_TO_STRING(EAction::FUEL);
        CASE_ENUM_TO_STRING(EAction::ENEMY_NORTH);
        CASE_ENUM_TO_STRING(EAction::ENEMY_EAST);
        CASE_ENUM_TO_STRING(EAction::ENEMY_SOUTH);
        CASE_ENUM_TO_STRING(EAction::ENEMY_WEST);
        CASE_ENUM_TO_STRING(EAction::STONE);
    case EAction::LAST:
        break;
    }
    throw util::CException("to_string(EAction) - invalid argument", util::from_Enum<int>(enum_value));
}

}
