
#include "testETileType.h"

#include "map/ETileType.h"
#include "util/CException.h"

namespace map {

void testETileType::testToString() {
    TS_ASSERT_EQUALS(to_string(ETileType::TOP_LEFT),            "ETileType::TOP_LEFT");
    TS_ASSERT_EQUALS(to_string(ETileType::RIGHT_TOP),           "ETileType::RIGHT_TOP");
    TS_ASSERT_EQUALS(to_string(ETileType::LEFT_BOTTOM),         "ETileType::LEFT_BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETileType::BOTTOM_RIGHT),        "ETileType::BOTTOM_RIGHT");
    TS_ASSERT_EQUALS(to_string(ETileType::GRASS),               "ETileType::GRASS");
    TS_ASSERT_EQUALS(to_string(ETileType::BUSH),                "ETileType::BUSH");
    TS_ASSERT_EQUALS(to_string(ETileType::ROAD),                "ETileType::ROAD");
    TS_ASSERT_EQUALS(to_string(ETileType::LEFT),                "ETileType::LEFT");
    TS_ASSERT_EQUALS(to_string(ETileType::RIGHT),               "ETileType::RIGHT");
    TS_ASSERT_EQUALS(to_string(ETileType::BOTTOM),              "ETileType::BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETileType::TOP),                 "ETileType::TOP");
    TS_ASSERT_EQUALS(to_string(ETileType::LEFT_RIGHT),          "ETileType::LEFT_RIGHT");
    TS_ASSERT_EQUALS(to_string(ETileType::TOP_BOTTOM),          "ETileType::TOP_BOTTOM");
    TS_ASSERT_EQUALS(to_string(ETileType::TOP_LEFT_CORNER),     "ETileType::TOP_LEFT_CORNER");
    TS_ASSERT_EQUALS(to_string(ETileType::RIGHT_TOP_CORNER),    "ETileType::RIGHT_TOP_CORNER");
    TS_ASSERT_EQUALS(to_string(ETileType::LEFT_BOTTOM_CORNER),  "ETileType::LEFT_BOTTOM_CORNER");
    TS_ASSERT_EQUALS(to_string(ETileType::BOTTOM_RIGHT_CORNER), "ETileType::BOTTOM_RIGHT_CORNER");
    TS_ASSERT_EQUALS(to_string(ETileType::LEFT_CORNERS),        "ETileType::LEFT_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETileType::TOP_CORNERS),         "ETileType::TOP_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETileType::BOTTOM_CORNERS),      "ETileType::BOTTOM_CORNERS");
    TS_ASSERT_EQUALS(to_string(ETileType::RIGHT_CORNERS),       "ETileType::RIGHT_CORNERS");

    TS_ASSERT_THROWS_EQUALS(to_string(ETileType::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(ETileType) - invalid argument");

    for (const auto tile : util::CEnumIterator<ETileType>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

