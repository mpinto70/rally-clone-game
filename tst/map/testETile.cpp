
#include "testETile.h"

#include "map/ETile.h"
#include "util/CException.h"

namespace map {

void testETile::testToString() {
    TS_ASSERT_EQUALS(to_string(ETile::TOP_LEFT),            "ETile::TOP_LEFT");
    TS_ASSERT_EQUALS(to_string(ETile::RIGHT_TOP),           "ETile::RIGHT_TOP");
    TS_ASSERT_EQUALS(to_string(ETile::LEFT_BOTTOM),         "ETile::LEFT_BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETile::BOTTOM_RIGHT),        "ETile::BOTTOM_RIGHT");
    TS_ASSERT_EQUALS(to_string(ETile::GRASS),               "ETile::GRASS");
    TS_ASSERT_EQUALS(to_string(ETile::BUSH),                "ETile::BUSH");
    TS_ASSERT_EQUALS(to_string(ETile::ROAD),                "ETile::ROAD");
    TS_ASSERT_EQUALS(to_string(ETile::LEFT),                "ETile::LEFT");
    TS_ASSERT_EQUALS(to_string(ETile::RIGHT),               "ETile::RIGHT");
    TS_ASSERT_EQUALS(to_string(ETile::BOTTOM),              "ETile::BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETile::TOP),                 "ETile::TOP");
    TS_ASSERT_EQUALS(to_string(ETile::LEFT_RIGHT),          "ETile::LEFT_RIGHT");
    TS_ASSERT_EQUALS(to_string(ETile::TOP_BOTTOM),          "ETile::TOP_BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETile::TOP_LEFT_CORNER),     "ETile::TOP_LEFT_CORNER");
    TS_ASSERT_EQUALS(to_string(ETile::RIGHT_TOP_CORNER),    "ETile::RIGHT_TOP_CORNER");
    TS_ASSERT_EQUALS(to_string(ETile::LEFT_BOTTOM_CORNER),  "ETile::LEFT_BOTTOM_CORNER");
    TS_ASSERT_EQUALS(to_string(ETile::BOTTOM_RIGHT_CORNER), "ETile::BOTTOM_RIGHT_CORNER");
    TS_ASSERT_EQUALS(to_string(ETile::LEFT_CORNERS),        "ETile::LEFT_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETile::TOP_CORNERS),         "ETile::TOP_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETile::BOTTOM_CORNERS),      "ETile::BOTTOM_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETile::RIGHT_CORNERS),       "ETile::RIGHT_CORNERS");

    TS_ASSERT_THROWS_EQUALS(to_string(ETile::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(ETile) - invalid argument");

    for (const auto tile : util::CEnumIterator<ETile>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

