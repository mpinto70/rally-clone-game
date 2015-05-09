
#include "testEDirection.h"

#include "car/EDirection.h"
#include "util/CException.h"

namespace car {

void testEDirection::testToString() {
    TS_ASSERT_EQUALS(to_string(EDirection::NONE),       "EDirection::NONE");
    TS_ASSERT_EQUALS(to_string(EDirection::NORTH),      "EDirection::NORTH");
    TS_ASSERT_EQUALS(to_string(EDirection::WEST),       "EDirection::WEST");
    TS_ASSERT_EQUALS(to_string(EDirection::SOUTH),      "EDirection::SOUTH");
    TS_ASSERT_EQUALS(to_string(EDirection::EAST),       "EDirection::EAST");

    TS_ASSERT_THROWS_EQUALS(to_string(EDirection::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "to_string(EDirection) - invalid argument");

    for (const auto tile : util::CEnumIterator<EDirection>()) {
        TS_ASSERT_THROWS_NOTHING(to_string(tile));
    }
}

}

