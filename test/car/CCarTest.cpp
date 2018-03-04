#include "car/CCar.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace car {

void verifyCreation(EDirection direction,
      EOrientation orientation) {
    const std::string msg = to_string(direction) + " / " + to_string(orientation);
    const CCar c(direction);
    EXPECT_EQ(c.direction(), direction) << msg;
    EXPECT_EQ(c.orientation(), orientation) << msg;
    EXPECT_EQ(c.nextDirection(), EDirection::NONE) << msg;
}
TEST(CCarTest, Creation) {
    const CCar c1(EDirection::NORTH);
    EXPECT_EQ(c1.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c1.direction(), EDirection::NORTH);
    EXPECT_EQ(c1.nextDirection(), EDirection::NONE);

    const CCar c2(EDirection::EAST);
    EXPECT_EQ(c2.orientation(), EOrientation::EAST);
    EXPECT_EQ(c2.direction(), EDirection::EAST);
    EXPECT_EQ(c2.nextDirection(), EDirection::NONE);

    verifyCreation(EDirection::NORTH, EOrientation::NORTH);
    verifyCreation(EDirection::EAST, EOrientation::EAST);
    verifyCreation(EDirection::SOUTH, EOrientation::SOUTH);
    verifyCreation(EDirection::WEST, EOrientation::WEST);
    verifyCreation(EDirection::NONE, EOrientation::NORTH);
}

TEST(CCarTest, InvalidCreation) {
    EXPECT_THROW(CCar c(EDirection::LAST),
          util::CException);
}

TEST(CCarTest, Turn) {
    CCar c(EDirection::NORTH);
    EXPECT_EQ(c.nextDirection(), EDirection::NONE);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::EAST);
    EXPECT_EQ(c.nextDirection(), EDirection::EAST);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::WEST);
    EXPECT_EQ(c.nextDirection(), EDirection::WEST);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::SOUTH);
    EXPECT_EQ(c.nextDirection(), EDirection::SOUTH);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::NORTH);
    EXPECT_EQ(c.nextDirection(), EDirection::NORTH);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::NONE);
    EXPECT_EQ(c.nextDirection(), EDirection::NONE);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);
}

static void verifyStepTurn(const EDirection direction,
      const EDirection nextDirection,
      const int step) {
    const std::string msg = to_string(direction) + " / " + to_string(nextDirection) + " (" + std::to_string(step) + ")";
    CCar c(direction);
    EXPECT_EQ(c.nextDirection(), EDirection::NONE) << msg;
    EXPECT_EQ(c.orientation(), CCar::convert(direction)) << msg;
    EXPECT_EQ(c.direction(), direction) << msg;

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
        EXPECT_EQ(c.nextDirection(), nextDirection) << msgi;
        EXPECT_EQ(c.orientation(), currentOrientation) << msgi;
        EXPECT_EQ(c.direction(), direction) << msgi;

        c.stepTurn();
    }

    EXPECT_EQ(c.nextDirection(), EDirection::NONE) << msg;
    EXPECT_EQ(c.orientation(), CCar::convert(nextDirection)) << msg;
    EXPECT_EQ(c.direction(), nextDirection) << msg;
}

static void verifyStepTurnDirections(const EDirection direction,
      const EDirection nextDirection,
      const int step) {
    verifyStepTurn(direction, nextDirection, step);
    verifyStepTurn(nextDirection, direction, -step);
}

TEST(CCarTest, StepTurn) {
    CCar c(EDirection::NORTH);
    EXPECT_EQ(c.nextDirection(), EDirection::NONE);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.turn(EDirection::EAST);
    EXPECT_EQ(c.nextDirection(), EDirection::EAST);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), EDirection::EAST);
    EXPECT_EQ(c.orientation(), EOrientation::NORTH_EAST);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), EDirection::EAST);
    EXPECT_EQ(c.orientation(), EOrientation::EAST_NORTH);
    EXPECT_EQ(c.direction(), EDirection::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), EDirection::NONE);
    EXPECT_EQ(c.orientation(), EOrientation::EAST);
    EXPECT_EQ(c.direction(), EDirection::EAST);

    verifyStepTurnDirections(EDirection::NORTH, EDirection::EAST, 1);
    verifyStepTurnDirections(EDirection::NORTH, EDirection::SOUTH, 1);
    verifyStepTurnDirections(EDirection::NORTH, EDirection::WEST, -1);
    verifyStepTurnDirections(EDirection::EAST, EDirection::SOUTH, 1);
    verifyStepTurnDirections(EDirection::EAST, EDirection::WEST, 1);
    verifyStepTurnDirections(EDirection::SOUTH, EDirection::WEST, 1);
}
}
