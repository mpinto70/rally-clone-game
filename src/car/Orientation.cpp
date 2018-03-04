
#include "Orientation.h"

#include "util/Exception.h"
#include "util/Util.h"

namespace car {

std::string to_string(Orientation enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(Orientation::NORTH);
        CASE_ENUM_TO_STRING(Orientation::NORTH_EAST);
        CASE_ENUM_TO_STRING(Orientation::EAST_NORTH);
        CASE_ENUM_TO_STRING(Orientation::EAST);
        CASE_ENUM_TO_STRING(Orientation::EAST_SOUTH);
        CASE_ENUM_TO_STRING(Orientation::SOUTH_EAST);
        CASE_ENUM_TO_STRING(Orientation::SOUTH);
        CASE_ENUM_TO_STRING(Orientation::SOUTH_WEST);
        CASE_ENUM_TO_STRING(Orientation::WEST_SOUTH);
        CASE_ENUM_TO_STRING(Orientation::WEST);
        CASE_ENUM_TO_STRING(Orientation::WEST_NORTH);
        CASE_ENUM_TO_STRING(Orientation::NORTH_WEST);
        case Orientation::LAST:
            break;
    }
    throw util::Exception("to_string(EOrientation) - invalid argument", util::from_Enum<int>(enum_value));
}
}
