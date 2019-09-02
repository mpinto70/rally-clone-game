#include "TileType.h"

#include "util/Exception.h"

namespace map {

std::string to_string(TileType enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileType::ROAD);
        CASE_ENUM_TO_STRING(TileType::TOP_LEFT);
        CASE_ENUM_TO_STRING(TileType::TOP);
        CASE_ENUM_TO_STRING(TileType::RIGHT_TOP);
        CASE_ENUM_TO_STRING(TileType::TILE_4);
        CASE_ENUM_TO_STRING(TileType::TILE_5);
        CASE_ENUM_TO_STRING(TileType::TILE_6);
        CASE_ENUM_TO_STRING(TileType::IGNORED_1);
        CASE_ENUM_TO_STRING(TileType::LEFT);
        CASE_ENUM_TO_STRING(TileType::GRASS);
        CASE_ENUM_TO_STRING(TileType::RIGHT);
        CASE_ENUM_TO_STRING(TileType::TILE_11);
        CASE_ENUM_TO_STRING(TileType::TILE_12);
        CASE_ENUM_TO_STRING(TileType::TILE_13);
        CASE_ENUM_TO_STRING(TileType::IGNORED_2);
        CASE_ENUM_TO_STRING(TileType::LEFT_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::BOTTOM);
        CASE_ENUM_TO_STRING(TileType::BOTTOM_RIGHT);
        CASE_ENUM_TO_STRING(TileType::TILE_18);
        CASE_ENUM_TO_STRING(TileType::TILE_19);
        CASE_ENUM_TO_STRING(TileType::TILE_20);
        CASE_ENUM_TO_STRING(TileType::BUSH);
        CASE_ENUM_TO_STRING(TileType::IGNORED_3);
        CASE_ENUM_TO_STRING(TileType::IGNORED_4);
        CASE_ENUM_TO_STRING(TileType::TILE_24);
        CASE_ENUM_TO_STRING(TileType::TILE_25);
        CASE_ENUM_TO_STRING(TileType::TILE_26);
        CASE_ENUM_TO_STRING(TileType::TILE_27);
        case TileType::LAST:
            break;
    }
    throw util::Exception("to_string(ETileType) - invalid argument", util::from_Enum<int>(enum_value));
}
}
