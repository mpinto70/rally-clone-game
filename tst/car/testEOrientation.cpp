
#include "testEOrientation.h"

#include "car/EOrientation.h"
#include "util/CException.h"

namespace car {

void testEOrientation::testToString() {
    TS_ASSERT_EQUALS(to_string(EOrientation::NORTH),        "EOrientation::NORTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::NORTH_WEST),   "EOrientation::NORTH_WEST");
    TS_ASSERT_EQUALS(to_string(EOrientation::WEST_NORTH),   "EOrientation::WEST_NORTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::WEST),         "EOrientation::WEST");
    TS_ASSERT_EQUALS(to_string(EOrientation::WEST_SOUTH),   "EOrientation::WEST_SOUTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::SOUTH_WEST),   "EOrientation::SOUTH_WEST");
    TS_ASSERT_EQUALS(to_string(EOrientation::SOUTH),        "EOrientation::SOUTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::SOUTH_EAST),   "EOrientation::SOUTH_EAST");
    TS_ASSERT_EQUALS(to_string(EOrientation::EAST_SOUTH),   "EOrientation::EAST_SOUTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::EAST),         "EOrientation::EAST");
    TS_ASSERT_EQUALS(to_string(EOrientation::EAST_NORTH),   "EOrientation::EAST_NORTH");
    TS_ASSERT_EQUALS(to_string(EOrientation::NORTH_EAST),   "EOrientation::NORTH_EAST");

    TS_ASSERT_THROWS_EQUALS(to_string(EOrientation::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(EOrientation) - invalid argument");

    for (const auto tile : util::CEnumIterator<EOrientation>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

