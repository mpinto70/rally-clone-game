
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
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::EAST);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::EAST);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::WEST);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::WEST);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::SOUTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::SOUTH);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::NORTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NORTH);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::NONE);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NONE);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);
}

static void verifyStepTurn(const EDirection direction,
                           const EDirection nextDirection,
                           const int step) {
    const std::string msg = to_string(direction) + " / " + to_string(nextDirection) + " (" + std::to_string(step) + ")";
    CCar c(direction);
    TSM_ASSERT_EQUALS(msg, c.nextDirection(), EDirection::NONE);
    TSM_ASSERT_EQUALS(msg, c.orientation(), CCar::convert(direction));
    TSM_ASSERT_EQUALS(msg, c.direction(), direction);

    c.turn(nextDirection);
    const auto initialOrientation = from_EOrientation<int>(c.orientation());
    const auto finalOrientation = from_EOrientation<int>(CCar::convert(nextDirection));
    for (int i = initialOrientation; i != finalOrientation; i += step) {
        if (i == from_EOrientation<int>(EOrientation::LAST))
            i = from_EOrientation<int>(EOrientation::FIRST);
        else if (i == from_EOrientation<int>(EOrientation::FIRST) - 1)
            i = from_EOrientation<int>(EOrientation::LAST) - 1;
        if (i == finalOrientation)
            break;
        const auto currentOrientation = to_EOrientation(i);
        const auto msgi = msg + " | " + to_string(currentOrientation) + " [" + std::to_string(i) + "]";
        TSM_ASSERT_EQUALS(msgi, c.nextDirection(), nextDirection);
        TSM_ASSERT_EQUALS(msgi, c.orientation(), currentOrientation);
        TSM_ASSERT_EQUALS(msgi, c.direction(), direction);

        c.stepTurn();
    }

    TSM_ASSERT_EQUALS(msg, c.nextDirection(), EDirection::NONE);
    TSM_ASSERT_EQUALS(msg, c.orientation(), CCar::convert(nextDirection));
    TSM_ASSERT_EQUALS(msg, c.direction(), nextDirection);
}

static void verifyStepTurnDirections(const EDirection direction,
                                     const EDirection nextDirection,
                                     const int step) {
    verifyStepTurn(direction, nextDirection, step);
    verifyStepTurn(nextDirection, direction, -step);
}

void testCCar::testStepTurn() {
    CCar c(EDirection::NORTH);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NONE);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.turn(EDirection::EAST);
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::EAST);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.stepTurn();
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::EAST);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::NORTH_EAST);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.stepTurn();
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::EAST);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::EAST_NORTH);
    TS_ASSERT_EQUALS(c.direction(), EDirection::NORTH);

    c.stepTurn();
    TS_ASSERT_EQUALS(c.nextDirection(), EDirection::NONE);
    TS_ASSERT_EQUALS(c.orientation(), EOrientation::EAST);
    TS_ASSERT_EQUALS(c.direction(), EDirection::EAST);

    verifyStepTurnDirections(EDirection::NORTH, EDirection::EAST, 1);
    verifyStepTurnDirections(EDirection::NORTH, EDirection::SOUTH, 1);
    verifyStepTurnDirections(EDirection::NORTH, EDirection::WEST, -1);
    verifyStepTurnDirections(EDirection::EAST, EDirection::SOUTH, 1);
    verifyStepTurnDirections(EDirection::EAST, EDirection::WEST, 1);
    verifyStepTurnDirections(EDirection::SOUTH, EDirection::WEST, 1);
}

}
