
#include "EDirection.h"

#include "util/CException.h"
#include "util/EUtil.h"

namespace car {

std::string to_string(EDirection enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(EDirection::NONE);
        CASE_ENUM_TO_STRING(EDirection::NORTH);
        CASE_ENUM_TO_STRING(EDirection::EAST);
        CASE_ENUM_TO_STRING(EDirection::SOUTH);
        CASE_ENUM_TO_STRING(EDirection::WEST);
        case EDirection::LAST:
            break;
    }
    throw util::CException("to_string(EDirection) - invalid argument", util::from_Enum<int>(enum_value));
}
}
