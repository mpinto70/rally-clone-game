#include "car/Orientation.h"
#include "util/Exception.h"

#include <gtest/gtest.h>

namespace car {

TEST(OrientationTest, ToString) {
    EXPECT_EQ(to_string(Orientation::NORTH), "Orientation::NORTH");
    EXPECT_EQ(to_string(Orientation::NORTH_WEST), "Orientation::NORTH_WEST");
    EXPECT_EQ(to_string(Orientation::WEST_NORTH), "Orientation::WEST_NORTH");
    EXPECT_EQ(to_string(Orientation::WEST), "Orientation::WEST");
    EXPECT_EQ(to_string(Orientation::WEST_SOUTH), "Orientation::WEST_SOUTH");
    EXPECT_EQ(to_string(Orientation::SOUTH_WEST), "Orientation::SOUTH_WEST");
    EXPECT_EQ(to_string(Orientation::SOUTH), "Orientation::SOUTH");
    EXPECT_EQ(to_string(Orientation::SOUTH_EAST), "Orientation::SOUTH_EAST");
    EXPECT_EQ(to_string(Orientation::EAST_SOUTH), "Orientation::EAST_SOUTH");
    EXPECT_EQ(to_string(Orientation::EAST), "Orientation::EAST");
    EXPECT_EQ(to_string(Orientation::EAST_NORTH), "Orientation::EAST_NORTH");
    EXPECT_EQ(to_string(Orientation::NORTH_EAST), "Orientation::NORTH_EAST");

    EXPECT_THROW(to_string(Orientation::LAST),
          util::Exception);

    for (const auto tile : util::EnumIterator<Orientation>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
