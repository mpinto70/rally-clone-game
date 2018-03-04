#include "car/Direction.h"

#include "util/Exception.h"

#include <gtest/gtest.h>

namespace car {

TEST(DirectionTest, ToString) {
    EXPECT_EQ(to_string(Direction::NONE), "Direction::NONE");
    EXPECT_EQ(to_string(Direction::NORTH), "Direction::NORTH");
    EXPECT_EQ(to_string(Direction::WEST), "Direction::WEST");
    EXPECT_EQ(to_string(Direction::SOUTH), "Direction::SOUTH");
    EXPECT_EQ(to_string(Direction::EAST), "Direction::EAST");

    EXPECT_THROW(to_string(Direction::LAST),
          util::Exception);

    for (const auto tile : util::EnumIterator<Direction>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
