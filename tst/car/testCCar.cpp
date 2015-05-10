
#include "testCCar.h"

#include "car/CCar.h"
#include "util/CException.h"

namespace car {

void verifyCreation(EDirection direction,
                EOrientation orientation) {
    const std::string msg = to_string(direction) + " / " + to_string(orientation);
    const CCar c(direction);
    TSM_ASSERT_EQUALS(msg, c.direction(), direction);
    TSM_ASSERT_EQUALS(msg, c.orientation(), orientation);
    TSM_ASSERT_EQUALS(msg, c.nextDirection(), EDirection::NONE);

}
void testCCar::testCreation() {
    const CCar c1(EDirection::NORTH);
    TS_ASSERT_EQUALS(c1.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c1.direction(), EDirection::NORTH);
    TS_ASSERT_EQUALS(c1.nextDirection(), EDirection::NONE);

    const CCar c2(EDirection::EAST);
    TS_ASSERT_EQUALS(c2.orientation(), EOrientation::EAST);
    TS_ASSERT_EQUALS(c2.direction(), EDirection::EAST);
    TS_ASSERT_EQUALS(c2.nextDirection(), EDirection::NONE);

    verifyCreation(EDirection::NORTH,   EOrientation::NORTH);
    verifyCreation(EDirection::EAST,    EOrientation::EAST);
    verifyCreation(EDirection::SOUTH,   EOrientation::SOUTH);
    verifyCreation(EDirection::WEST,    EOrientation::WEST);
    verifyCreation(EDirection::NONE,    EOrientation::NORTH);
}

void testCCar::testInvalidCreation() {
    TS_ASSERT_THROWS_EQUALS(CCar c(EDirection::LAST),
                            util::CException & e,
                            std::string(e.what()),
                            "CCar - invalid direction");
}

void testCCar::testTurn() {
    CCar c(EDirection::NORTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NONE);

    c.turn(EDirection::EAST);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::EAST);

    c.turn(EDirection::WEST);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::WEST);

    c.turn(EDirection::SOUTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::SOUTH);

    c.turn(EDirection::NORTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NORTH);

    c.turn(EDirection::NONE);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NONE);
}

}
