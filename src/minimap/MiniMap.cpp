#include "MiniMap.h"

#include "util/Exception.h"
#include "util/Util.h"

namespace minimap {

std::string to_string(Type enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(Type::PLAYER_ON);
        CASE_ENUM_TO_STRING(Type::PLAYER_OFF);
        CASE_ENUM_TO_STRING(Type::FUEL);
        CASE_ENUM_TO_STRING(Type::ENEMY);
        case Type::LAST:
            break;
    }
    throw util::Exception("to_string(minimap::Type) - invalid argument", util::from_Enum<int>(enum_value));
}
}
