#include "map/ETileType.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace map {

TEST(ETileTypeTest, ToString) {
    EXPECT_EQ(to_string(ETileType::TOP_LEFT), "ETileType::TOP_LEFT");
    EXPECT_EQ(to_string(ETileType::RIGHT_TOP), "ETileType::RIGHT_TOP");
    EXPECT_EQ(to_string(ETileType::LEFT_BOTTOM), "ETileType::LEFT_BOTTOM");
    EXPECT_EQ(to_string(ETileType::BOTTOM_RIGHT), "ETileType::BOTTOM_RIGHT");
    EXPECT_EQ(to_string(ETileType::GRASS), "ETileType::GRASS");
    EXPECT_EQ(to_string(ETileType::BUSH), "ETileType::BUSH");
    EXPECT_EQ(to_string(ETileType::ROAD), "ETileType::ROAD");
    EXPECT_EQ(to_string(ETileType::LEFT), "ETileType::LEFT");
    EXPECT_EQ(to_string(ETileType::RIGHT), "ETileType::RIGHT");
    EXPECT_EQ(to_string(ETileType::BOTTOM), "ETileType::BOTTOM");
    EXPECT_EQ(to_string(ETileType::TOP), "ETileType::TOP");
    EXPECT_EQ(to_string(ETileType::LEFT_RIGHT), "ETileType::LEFT_RIGHT");
    EXPECT_EQ(to_string(ETileType::TOP_BOTTOM), "ETileType::TOP_BOTTOM");
    EXPECT_EQ(to_string(ETileType::TOP_LEFT_CORNER), "ETileType::TOP_LEFT_CORNER");
    EXPECT_EQ(to_string(ETileType::RIGHT_TOP_CORNER), "ETileType::RIGHT_TOP_CORNER");
    EXPECT_EQ(to_string(ETileType::LEFT_BOTTOM_CORNER), "ETileType::LEFT_BOTTOM_CORNER");
    EXPECT_EQ(to_string(ETileType::BOTTOM_RIGHT_CORNER), "ETileType::BOTTOM_RIGHT_CORNER");
    EXPECT_EQ(to_string(ETileType::LEFT_CORNERS), "ETileType::LEFT_CORNERS");
    EXPECT_EQ(to_string(ETileType::TOP_CORNERS), "ETileType::TOP_CORNERS");
    EXPECT_EQ(to_string(ETileType::BOTTOM_CORNERS), "ETileType::BOTTOM_CORNERS");
    EXPECT_EQ(to_string(ETileType::RIGHT_CORNERS), "ETileType::RIGHT_CORNERS");

    EXPECT_THROW(to_string(ETileType::LAST), util::CException);

    for (const auto type : util::CEnumIterator<ETileType>()) {
        EXPECT_NO_THROW(to_string(type));
    }
}
}
