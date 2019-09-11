#include "TileType.h"

#include "util/Exception.h"

namespace map {

std::string to_string(TileType enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileType::ROAD);
        CASE_ENUM_TO_STRING(TileType::N_W);
        CASE_ENUM_TO_STRING(TileType::N);
        CASE_ENUM_TO_STRING(TileType::N_E);
        CASE_ENUM_TO_STRING(TileType::N_W_SE);
        CASE_ENUM_TO_STRING(TileType::N_W_E);
        CASE_ENUM_TO_STRING(TileType::N_E_SW);
        CASE_ENUM_TO_STRING(TileType::W);
        CASE_ENUM_TO_STRING(TileType::GRASS);
        CASE_ENUM_TO_STRING(TileType::E);
        CASE_ENUM_TO_STRING(TileType::N_W_BOTTOM);
        CASE_ENUM_TO_STRING(TileType::NE_NW_SW_SE);
        CASE_ENUM_TO_STRING(TileType::S_E_TOP);
        CASE_ENUM_TO_STRING(TileType::N_W_S_E);
        CASE_ENUM_TO_STRING(TileType::W_S);
        CASE_ENUM_TO_STRING(TileType::S);
        CASE_ENUM_TO_STRING(TileType::S_E);
        CASE_ENUM_TO_STRING(TileType::W_S_NE);
        CASE_ENUM_TO_STRING(TileType::W_S_E);
        CASE_ENUM_TO_STRING(TileType::S_E_NW);
        CASE_ENUM_TO_STRING(TileType::BUSH);
        CASE_ENUM_TO_STRING(TileType::W_E);
        CASE_ENUM_TO_STRING(TileType::N_S);
        CASE_ENUM_TO_STRING(TileType::N_SW_SE);
        CASE_ENUM_TO_STRING(TileType::W_NE_SE);
        CASE_ENUM_TO_STRING(TileType::S_NE_NW);
        CASE_ENUM_TO_STRING(TileType::E_NW_SW);
        CASE_ENUM_TO_STRING(TileType::NE_NW);
        CASE_ENUM_TO_STRING(TileType::NW_SW);
        CASE_ENUM_TO_STRING(TileType::SW_SE);
        CASE_ENUM_TO_STRING(TileType::NE_SE);
        CASE_ENUM_TO_STRING(TileType::NE);
        CASE_ENUM_TO_STRING(TileType::NW);
        CASE_ENUM_TO_STRING(TileType::SW);
        CASE_ENUM_TO_STRING(TileType::SE);
        CASE_ENUM_TO_STRING(TileType::NE_NW_SW);
        CASE_ENUM_TO_STRING(TileType::NE_NW_SE);
        CASE_ENUM_TO_STRING(TileType::NE_SW_SE);
        CASE_ENUM_TO_STRING(TileType::NW_SW_SE);
        CASE_ENUM_TO_STRING(TileType::NW_SE);
        CASE_ENUM_TO_STRING(TileType::NE_SW);
        case TileType::LAST:
            break;
    }
    throw util::Exception("to_string(ETileType) - invalid argument", util::from_Enum<int>(enum_value));
}
}
