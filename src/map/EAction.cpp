
#include "EAction.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(EAction enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(EAction::NONE);
            CASE_ENUM_TO_STRING(EAction::FUEL);
            CASE_ENUM_TO_STRING(EAction::ENEMY_UP);
            CASE_ENUM_TO_STRING(EAction::ENEMY_LEFT);
            CASE_ENUM_TO_STRING(EAction::ENEMY_DOWN);
            CASE_ENUM_TO_STRING(EAction::ENEMY_RIGHT);
            CASE_ENUM_TO_STRING(EAction::STONE);
        case EAction::LAST:
            break;
    }
    throw util::CException("to_string(EAction) - invalid argument", util::from_Enum<int>(enum_value));
}

}
