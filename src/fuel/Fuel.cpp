#include "Fuel.h"

#include "util/Exception.h"
#include "util/Util.h"

namespace fuel {

std::string to_string(Type enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(Type::FUEL);
        CASE_ENUM_TO_STRING(Type::FUEL_S);
        CASE_ENUM_TO_STRING(Type::FUEL_L);
        case Type::LAST:
            break;
    }
    throw util::Exception("to_string(Type) - invalid argument", util::from_Enum<int>(enum_value));
}
}
