#include "TileType.h"

#include "util/Exception.h"

namespace map {

std::string to_string(TileType enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileType::ROAD);
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT);
        CASE_ENUM_TO_STRING(TileType::TOP);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP);
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT_SE);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP_LEFT);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP_SW);
        CASE_ENUM_TO_STRING(TileType::LEFT);
        CASE_ENUM_TO_STRING(TileType::GRASS);
        CASE_ENUM_TO_STRING(TileType::RIGHT);
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::NW_SW_SE_NE);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT_TOP);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::BOTTOM);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM_NE);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM_RIGHT);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT_NW);
        CASE_ENUM_TO_STRING(TileType::BUSH);
        CASE_ENUM_TO_STRING(TileType::TOP_SW_SE);
        CASE_ENUM_TO_STRING(TileType::LEFT_SE_NE);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_NE_NW);
        CASE_ENUM_TO_STRING(TileType::RIGHT_NW_SW);
        case TileType::LAST:
            break;
    }
    throw util::Exception("to_string(ETileType) - invalid argument", util::from_Enum<int>(enum_value));
}
}
