
#include "ETileType.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(ETileType enum_value) {
    switch (enum_value) {
            CASE_ENUM_TO_STRING(ETileType::TOP_LEFT);
            CASE_ENUM_TO_STRING(ETileType::RIGHT_TOP);
            CASE_ENUM_TO_STRING(ETileType::LEFT_BOTTOM);
            CASE_ENUM_TO_STRING(ETileType::BOTTOM_RIGHT);
            CASE_ENUM_TO_STRING(ETileType::GRASS);
            CASE_ENUM_TO_STRING(ETileType::BUSH);
            CASE_ENUM_TO_STRING(ETileType::ROAD);
            CASE_ENUM_TO_STRING(ETileType::LEFT);
            CASE_ENUM_TO_STRING(ETileType::RIGHT);
            CASE_ENUM_TO_STRING(ETileType::BOTTOM);
            CASE_ENUM_TO_STRING(ETileType::TOP);
            CASE_ENUM_TO_STRING(ETileType::LEFT_RIGHT);
            CASE_ENUM_TO_STRING(ETileType::TOP_BOTTOM);
            CASE_ENUM_TO_STRING(ETileType::TOP_LEFT_CORNER);
            CASE_ENUM_TO_STRING(ETileType::RIGHT_TOP_CORNER);
            CASE_ENUM_TO_STRING(ETileType::LEFT_BOTTOM_CORNER);
            CASE_ENUM_TO_STRING(ETileType::BOTTOM_RIGHT_CORNER);
            CASE_ENUM_TO_STRING(ETileType::LEFT_CORNERS);
            CASE_ENUM_TO_STRING(ETileType::TOP_CORNERS);
            CASE_ENUM_TO_STRING(ETileType::BOTTOM_CORNERS);
            CASE_ENUM_TO_STRING(ETileType::RIGHT_CORNERS);
        case ETileType::LAST:
            break;
    }
    throw util::CException("to_string(ETileType) - invalid argument", util::from_Enum<int>(enum_value));
}

}
