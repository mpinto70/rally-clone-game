#include "car/Car.h"
#include "util/Exception.h"

#include <gtest/gtest.h>

namespace car {

void verifyCreation(Direction direction,
      Orientation orientation) {
    const std::string msg = to_string(direction) + " / " + to_string(orientation);
    const Car c(direction);
    EXPECT_EQ(c.direction(), direction) << msg;
    EXPECT_EQ(c.orientation(), orientation) << msg;
    EXPECT_EQ(c.nextDirection(), Direction::NONE) << msg;
}
TEST(CCarTest, Creation) {
    const Car c1(Direction::NORTH);
    EXPECT_EQ(c1.orientation(), Orientation::NORTH);
    EXPECT_EQ(c1.direction(), Direction::NORTH);
    EXPECT_EQ(c1.nextDirection(), Direction::NONE);

    const Car c2(Direction::EAST);
    EXPECT_EQ(c2.orientation(), Orientation::EAST);
    EXPECT_EQ(c2.direction(), Direction::EAST);
    EXPECT_EQ(c2.nextDirection(), Direction::NONE);

    verifyCreation(Direction::NORTH, Orientation::NORTH);
    verifyCreation(Direction::EAST, Orientation::EAST);
    verifyCreation(Direction::SOUTH, Orientation::SOUTH);
    verifyCreation(Direction::WEST, Orientation::WEST);
    verifyCreation(Direction::NONE, Orientation::NORTH);
}

TEST(CCarTest, InvalidCreation) {
    EXPECT_THROW(Car c(Direction::LAST),
          util::Exception);
}

TEST(CCarTest, Turn) {
    Car c(Direction::NORTH);
    EXPECT_EQ(c.nextDirection(), Direction::NONE);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::EAST);
    EXPECT_EQ(c.nextDirection(), Direction::EAST);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::WEST);
    EXPECT_EQ(c.nextDirection(), Direction::WEST);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::SOUTH);
    EXPECT_EQ(c.nextDirection(), Direction::SOUTH);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::NORTH);
    EXPECT_EQ(c.nextDirection(), Direction::NORTH);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::NONE);
    EXPECT_EQ(c.nextDirection(), Direction::NONE);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);
}

static void verifyStepTurn(const Direction direction,
      const Direction nextDirection,
      const int step) {
    const std::string msg = to_string(direction) + " / " + to_string(nextDirection) + " (" + std::to_string(step) + ")";
    Car c(direction);
    EXPECT_EQ(c.nextDirection(), Direction::NONE) << msg;
    EXPECT_EQ(c.orientation(), Car::convert(direction)) << msg;
    EXPECT_EQ(c.direction(), direction) << msg;

    c.turn(nextDirection);
    const auto initialOrientation = from_Orientation<int>(c.orientation());
    const auto finalOrientation = from_Orientation<int>(Car::convert(nextDirection));
    for (int i = initialOrientation; i != finalOrientation; i += step) {
        if (i == from_Orientation<int>(Orientation::LAST))
            i = from_Orientation<int>(Orientation::FIRST);
        else if (i == from_Orientation<int>(Orientation::FIRST) - 1)
            i = from_Orientation<int>(Orientation::LAST) - 1;
        if (i == finalOrientation)
            break;
        const auto currentOrientation = to_Orientation(i);
        const auto msgi = msg + " | " + to_string(currentOrientation) + " [" + std::to_string(i) + "]";
        EXPECT_EQ(c.nextDirection(), nextDirection) << msgi;
        EXPECT_EQ(c.orientation(), currentOrientation) << msgi;
        EXPECT_EQ(c.direction(), direction) << msgi;

        c.stepTurn();
    }

    EXPECT_EQ(c.nextDirection(), Direction::NONE) << msg;
    EXPECT_EQ(c.orientation(), Car::convert(nextDirection)) << msg;
    EXPECT_EQ(c.direction(), nextDirection) << msg;
}

static void verifyStepTurnDirections(const Direction direction,
      const Direction nextDirection,
      const int step) {
    verifyStepTurn(direction, nextDirection, step);
    verifyStepTurn(nextDirection, direction, -step);
}

TEST(CCarTest, StepTurn) {
    Car c(Direction::NORTH);
    EXPECT_EQ(c.nextDirection(), Direction::NONE);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.turn(Direction::EAST);
    EXPECT_EQ(c.nextDirection(), Direction::EAST);
    EXPECT_EQ(c.orientation(), Orientation::NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), Direction::EAST);
    EXPECT_EQ(c.orientation(), Orientation::NORTH_EAST);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), Direction::EAST);
    EXPECT_EQ(c.orientation(), Orientation::EAST_NORTH);
    EXPECT_EQ(c.direction(), Direction::NORTH);

    c.stepTurn();
    EXPECT_EQ(c.nextDirection(), Direction::NONE);
    EXPECT_EQ(c.orientation(), Orientation::EAST);
    EXPECT_EQ(c.direction(), Direction::EAST);

    verifyStepTurnDirections(Direction::NORTH, Direction::EAST, 1);
    verifyStepTurnDirections(Direction::NORTH, Direction::SOUTH, 1);
    verifyStepTurnDirections(Direction::NORTH, Direction::WEST, -1);
    verifyStepTurnDirections(Direction::EAST, Direction::SOUTH, 1);
    verifyStepTurnDirections(Direction::EAST, Direction::WEST, 1);
    verifyStepTurnDirections(Direction::SOUTH, Direction::WEST, 1);
}
}
