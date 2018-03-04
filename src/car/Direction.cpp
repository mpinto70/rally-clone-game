#include "Direction.h"

#include "util/Exception.h"
#include "util/Util.h"

namespace car {

std::string to_string(Direction enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(Direction::NONE);
        CASE_ENUM_TO_STRING(Direction::NORTH);
        CASE_ENUM_TO_STRING(Direction::EAST);
        CASE_ENUM_TO_STRING(Direction::SOUTH);
        CASE_ENUM_TO_STRING(Direction::WEST);
        case Direction::LAST:
            break;
    }
    throw util::Exception("to_string(EDirection) - invalid argument", util::from_Enum<int>(enum_value));
}
}
