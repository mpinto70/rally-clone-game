
#include "EOrientation.h"

#include "util/CException.h"
#include "util/EUtil.h"

namespace car {

std::string to_string(EOrientation enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(EOrientation::NORTH);
            CASE_ENUM_TO_STRING(EOrientation::NORTH_EAST);
            CASE_ENUM_TO_STRING(EOrientation::EAST_NORTH);
            CASE_ENUM_TO_STRING(EOrientation::EAST);
            CASE_ENUM_TO_STRING(EOrientation::EAST_SOUTH);
            CASE_ENUM_TO_STRING(EOrientation::SOUTH_EAST);
            CASE_ENUM_TO_STRING(EOrientation::SOUTH);
            CASE_ENUM_TO_STRING(EOrientation::SOUTH_WEST);
            CASE_ENUM_TO_STRING(EOrientation::WEST_SOUTH);
            CASE_ENUM_TO_STRING(EOrientation::WEST);
            CASE_ENUM_TO_STRING(EOrientation::WEST_NORTH);
            CASE_ENUM_TO_STRING(EOrientation::NORTH_WEST);
        case EOrientation::LAST:
            break;
    }
    throw util::CException("to_string(EOrientation) - invalid argument", util::from_Enum<int>(enum_value));
}

}
