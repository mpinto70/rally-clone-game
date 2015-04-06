
#include "EAction.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(EAction enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(EAction::NONE);
            CASE_ENUM_TO_STRING(EAction::CREATE_ENEMY);
            CASE_ENUM_TO_STRING(EAction::CREATE_STONE);
        case EAction::LAST:
            break;
    }
    throw util::CException("to_string(EAction) - invalid argument", util::from_Enum<int>(enum_value));
}

}