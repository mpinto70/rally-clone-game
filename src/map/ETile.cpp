
#include "ETile.h"
#include "map/EMapUtil.h"

#include "util/CException.h"

namespace map {

std::string to_string(ETile tile) {
    switch (tile) {
            CASE_ENUM_TO_STRING(ETile::TOP_LEFT);
            CASE_ENUM_TO_STRING(ETile::RIGHT_TOP);
            CASE_ENUM_TO_STRING(ETile::LEFT_BOTTOM);
            CASE_ENUM_TO_STRING(ETile::BOTTOM_RIGHT);
            CASE_ENUM_TO_STRING(ETile::GRASS);
            CASE_ENUM_TO_STRING(ETile::BUSH);
            CASE_ENUM_TO_STRING(ETile::ROAD);
            CASE_ENUM_TO_STRING(ETile::LEFT);
            CASE_ENUM_TO_STRING(ETile::RIGHT);
            CASE_ENUM_TO_STRING(ETile::BOTTOM);
            CASE_ENUM_TO_STRING(ETile::TOP);
            CASE_ENUM_TO_STRING(ETile::LEFT_RIGHT);
            CASE_ENUM_TO_STRING(ETile::TOP_BOTTOM);
            CASE_ENUM_TO_STRING(ETile::TOP_LEFT_CORNER);
            CASE_ENUM_TO_STRING(ETile::RIGHT_TOP_CORNER);
            CASE_ENUM_TO_STRING(ETile::LEFT_BOTTOM_CORNER);
            CASE_ENUM_TO_STRING(ETile::BOTTOM_RIGHT_CORNER);
            CASE_ENUM_TO_STRING(ETile::LEFT_CORNERS);
            CASE_ENUM_TO_STRING(ETile::TOP_CORNERS);
            CASE_ENUM_TO_STRING(ETile::BOTTOM_CORNERS);
            CASE_ENUM_TO_STRING(ETile::RIGHT_CORNERS);
        case ETile::LAST:
            break;
    }
    throw util::CException("to_string(ETile) - invalid argument", util::from_Enum<int>(tile));
}

}
