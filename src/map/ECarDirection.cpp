
#include "ECarDirection.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(ECarDirection enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(ECarDirection::NORTH);
            CASE_ENUM_TO_STRING(ECarDirection::NORTH_EAST);
            CASE_ENUM_TO_STRING(ECarDirection::EAST_NORTH);
            CASE_ENUM_TO_STRING(ECarDirection::EAST);
            CASE_ENUM_TO_STRING(ECarDirection::EAST_SOUTH);
            CASE_ENUM_TO_STRING(ECarDirection::SOUTH_EAST);
            CASE_ENUM_TO_STRING(ECarDirection::SOUTH);
            CASE_ENUM_TO_STRING(ECarDirection::SOUTH_WEST);
            CASE_ENUM_TO_STRING(ECarDirection::WEST_SOUTH);
            CASE_ENUM_TO_STRING(ECarDirection::WEST);
            CASE_ENUM_TO_STRING(ECarDirection::WEST_NORTH);
            CASE_ENUM_TO_STRING(ECarDirection::NORTH_WEST);
        case ECarDirection::LAST:
            break;
    }
    throw util::CException("to_string(ECarDirection) - invalid argument", util::from_Enum<int>(enum_value));
}

}
