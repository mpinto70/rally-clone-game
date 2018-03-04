#include "car/EDirection.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace car {

TEST(EDirectionTest, ToString) {
    EXPECT_EQ(to_string(EDirection::NONE), "EDirection::NONE");
    EXPECT_EQ(to_string(EDirection::NORTH), "EDirection::NORTH");
    EXPECT_EQ(to_string(EDirection::WEST), "EDirection::WEST");
    EXPECT_EQ(to_string(EDirection::SOUTH), "EDirection::SOUTH");
    EXPECT_EQ(to_string(EDirection::EAST), "EDirection::EAST");

    EXPECT_THROW(to_string(EDirection::LAST),
          util::CException);

    for (const auto tile : util::CEnumIterator<EDirection>()) {
        EXPECT_NO_THROW(to_string(tile));
    }
}
}
