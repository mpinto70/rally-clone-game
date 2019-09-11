#include "map/TileType.h"

#include "util/Exception.h"

#include <gtest/gtest.h>

namespace map {

TEST(TileTypeTest, ToString) {
    EXPECT_EQ(to_string(TileType::N_W), "TileType::N_W");
    EXPECT_EQ(to_string(TileType::N_E), "TileType::N_E");
    EXPECT_EQ(to_string(TileType::W_S), "TileType::W_S");
    EXPECT_EQ(to_string(TileType::S_E), "TileType::S_E");
    EXPECT_EQ(to_string(TileType::GRASS), "TileType::GRASS");
    EXPECT_EQ(to_string(TileType::BUSH), "TileType::BUSH");
    EXPECT_EQ(to_string(TileType::ROAD), "TileType::ROAD");
    EXPECT_EQ(to_string(TileType::W), "TileType::W");
    EXPECT_EQ(to_string(TileType::E), "TileType::E");
    EXPECT_EQ(to_string(TileType::S), "TileType::S");
    EXPECT_EQ(to_string(TileType::N), "TileType::N");

    EXPECT_THROW(to_string(TileType::LAST), util::Exception);

    for (const auto type : util::EnumIterator<TileType>()) {
        EXPECT_NO_THROW(to_string(type));
    }
}
}
