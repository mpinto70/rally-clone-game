
#include "EDirection.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace car {

std::string to_string(EDirection enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(EDirection::NORTH);
            CASE_ENUM_TO_STRING(EDirection::NORTH_EAST);
            CASE_ENUM_TO_STRING(EDirection::EAST_NORTH);
            CASE_ENUM_TO_STRING(EDirection::EAST);
            CASE_ENUM_TO_STRING(EDirection::EAST_SOUTH);
            CASE_ENUM_TO_STRING(EDirection::SOUTH_EAST);
            CASE_ENUM_TO_STRING(EDirection::SOUTH);
            CASE_ENUM_TO_STRING(EDirection::SOUTH_WEST);
            CASE_ENUM_TO_STRING(EDirection::WEST_SOUTH);
            CASE_ENUM_TO_STRING(EDirection::WEST);
            CASE_ENUM_TO_STRING(EDirection::WEST_NORTH);
            CASE_ENUM_TO_STRING(EDirection::NORTH_WEST);
        case EDirection::LAST:
            break;
    }
    throw util::CException("to_string(ECarDirection) - invalid argument", util::from_Enum<int>(enum_value));
}

}
