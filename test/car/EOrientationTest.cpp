#include "car/EOrientation.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace car {

TEST(EOrientationTest, ToString) {
    EXPECT_EQ(to_string(EOrientation::NORTH), "EOrientation::NORTH");
    EXPECT_EQ(to_string(EOrientation::NORTH_WEST), "EOrientation::NORTH_WEST");
    EXPECT_EQ(to_string(EOrientation::WEST_NORTH), "EOrientation::WEST_NORTH");
    EXPECT_EQ(to_string(EOrientation::WEST), "EOrientation::WEST");
    EXPECT_EQ(to_string(EOrientation::WEST_SOUTH), "EOrientation::WEST_SOUTH");
    EXPECT_EQ(to_string(EOrientation::SOUTH_WEST), "EOrientation::SOUTH_WEST");
    EXPECT_EQ(to_string(EOrientation::SOUTH), "EOrientation::SOUTH");
    EXPECT_EQ(to_string(EOrientation::SOUTH_EAST), "EOrientation::SOUTH_EAST");
    EXPECT_EQ(to_string(EOrientation::EAST_SOUTH), "EOrientation::EAST_SOUTH");
    EXPECT_EQ(to_string(EOrientation::EAST), "EOrientation::EAST");
    EXPECT_EQ(to_string(EOrientation::EAST_NORTH), "EOrientation::EAST_NORTH");
    EXPECT_EQ(to_string(EOrientation::NORTH_EAST), "EOrientation::NORTH_EAST");

    EXPECT_THROW(to_string(EOrientation::LAST),
          util::CException);

    for (const auto tile : util::CEnumIterator<EOrientation>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
