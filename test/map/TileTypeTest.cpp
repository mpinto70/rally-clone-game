#include "map/TileType.h"
#include "util/Exception.h"

#include <gtest/gtest.h>

namespace map {

TEST(TileTypeTest, ToString) {
    EXPECT_EQ(to_string(TileType::TOP_LEFT), "TileType::TOP_LEFT");
    EXPECT_EQ(to_string(TileType::RIGHT_TOP), "TileType::RIGHT_TOP");
    EXPECT_EQ(to_string(TileType::LEFT_BOTTOM), "TileType::LEFT_BOTTOM");
    EXPECT_EQ(to_string(TileType::BOTTOM_RIGHT), "TileType::BOTTOM_RIGHT");
    EXPECT_EQ(to_string(TileType::GRASS), "TileType::GRASS");
    EXPECT_EQ(to_string(TileType::BUSH), "TileType::BUSH");
    EXPECT_EQ(to_string(TileType::ROAD), "TileType::ROAD");
    EXPECT_EQ(to_string(TileType::LEFT), "TileType::LEFT");
    EXPECT_EQ(to_string(TileType::RIGHT), "TileType::RIGHT");
    EXPECT_EQ(to_string(TileType::BOTTOM), "TileType::BOTTOM");
    EXPECT_EQ(to_string(TileType::TOP), "TileType::TOP");
    EXPECT_EQ(to_string(TileType::LEFT_RIGHT), "TileType::LEFT_RIGHT");
    EXPECT_EQ(to_string(TileType::TOP_BOTTOM), "TileType::TOP_BOTTOM");
    EXPECT_EQ(to_string(TileType::TOP_LEFT_CORNER), "TileType::TOP_LEFT_CORNER");
    EXPECT_EQ(to_string(TileType::RIGHT_TOP_CORNER), "TileType::RIGHT_TOP_CORNER");
    EXPECT_EQ(to_string(TileType::LEFT_BOTTOM_CORNER), "TileType::LEFT_BOTTOM_CORNER");
    EXPECT_EQ(to_string(TileType::BOTTOM_RIGHT_CORNER), "TileType::BOTTOM_RIGHT_CORNER");
    EXPECT_EQ(to_string(TileType::LEFT_CORNERS), "TileType::LEFT_CORNERS");
    EXPECT_EQ(to_string(TileType::TOP_CORNERS), "TileType::TOP_CORNERS");
    EXPECT_EQ(to_string(TileType::BOTTOM_CORNERS), "TileType::BOTTOM_CORNERS");
    EXPECT_EQ(to_string(TileType::RIGHT_CORNERS), "TileType::RIGHT_CORNERS");

    EXPECT_THROW(to_string(TileType::LAST), util::Exception);

    for (const auto type : util::EnumIterator<TileType>()) {
        EXPECT_NO_THROW(to_string(type));
    }
}
}
