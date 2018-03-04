#include "TileType.h"

#include "util/Exception.h"
#include "map/MapUtil.h"


namespace map {

std::string to_string(TileType enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT);
        CASE_ENUM_TO_STRING(TileType::GRASS);
        CASE_ENUM_TO_STRING(TileType::BUSH);
        CASE_ENUM_TO_STRING(TileType::ROAD);
        CASE_ENUM_TO_STRING(TileType::LEFT);
        CASE_ENUM_TO_STRING(TileType::RIGHT);
        CASE_ENUM_TO_STRING(TileType::BOTTOM);
        CASE_ENUM_TO_STRING(TileType::TOP);
        CASE_ENUM_TO_STRING(TileType::LEFT_RIGHT);
        CASE_ENUM_TO_STRING(TileType::TOP_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT_CORNER);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP_CORNER);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM_CORNER);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT_CORNER);
        CASE_ENUM_TO_STRING(TileType::LEFT_CORNERS);
        CASE_ENUM_TO_STRING(TileType::TOP_CORNERS);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_CORNERS);
        CASE_ENUM_TO_STRING(TileType::RIGHT_CORNERS);
        case TileType::LAST:
            break;
    }
    throw util::Exception("to_string(ETileType) - invalid argument", util::from_Enum<int>(enum_value));
}
}
