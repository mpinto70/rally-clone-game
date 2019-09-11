#include "map/Map.h"

#include "util/Exception.h"

#include <gtest/gtest.h>

namespace map {

TEST(MapTest, Creation) {
    std::vector<Tile> tiles = {
        Tile{ TileType::ROAD, Action::STONE_1 },
        Tile{ TileType::BUSH, Action::NONE }
    };

    const Map m1(1, 2, tiles);
    EXPECT_EQ(m1.width(), 1u);
    EXPECT_EQ(m1.height(), 2u);
    EXPECT_EQ(m1.tiles(), tiles);

    tiles = {
        Tile{ TileType::ROAD, Action::ENEMY_NORTH },
        Tile{ TileType::BUSH, Action::NONE },
        Tile{TileType::S, Action::NONE },
        Tile{ TileType::GRASS, Action::NONE },
        Tile{TileType::W, Action::NONE },
        Tile{TileType::E, Action::NONE }
    };

    const Map m2(2, 3, tiles);
    EXPECT_EQ(m2.width(), 2u);
    EXPECT_EQ(m2.height(), 3u);
    EXPECT_EQ(m2.tiles(), tiles);
}

TEST(MapTest, InvalidCreation) {
    EXPECT_THROW(Map(0, 2, { Tile{ TileType::ROAD, Action::STONE_1 }, Tile{ TileType::BUSH, Action::NONE } }),
          std::invalid_argument);

    EXPECT_THROW(Map(1, 0, { Tile{ TileType::ROAD, Action::STONE_1 }, Tile{ TileType::BUSH, Action::NONE } }),
          std::invalid_argument);

    EXPECT_THROW(Map(1, 3, { Tile{ TileType::ROAD, Action::STONE_1 }, Tile{ TileType::BUSH, Action::NONE } }),
          std::invalid_argument);
}

TEST(MapTest, Indexing) {
    std::vector<Tile> tiles = {
        Tile{ TileType::ROAD, Action::STONE_1 },
        Tile{ TileType::BUSH, Action::NONE }
    };

    const Map m1(1, 2, tiles);
    EXPECT_EQ(m1(0, 0), Tile(TileType::ROAD, Action::STONE_1));
    EXPECT_EQ(m1(0, 1), Tile(TileType::BUSH, Action::NONE));
    EXPECT_THROW(m1(1, 0),
          util::Exception);
    EXPECT_THROW(m1(0, 2),
          util::Exception);

    const Map m2(2, 1, tiles);
    EXPECT_EQ(m2(0, 0), Tile(TileType::ROAD, Action::STONE_1));
    EXPECT_EQ(m2(1, 0), Tile(TileType::BUSH, Action::NONE));
    EXPECT_THROW(m2(2, 0), util::Exception);
    EXPECT_THROW(m2(0, 1), util::Exception);

    tiles = {
        Tile{ TileType::ROAD, Action::ENEMY_NORTH },
        Tile{ TileType::BUSH, Action::NONE },
        Tile{TileType::S, Action::NONE },
        Tile{ TileType::GRASS, Action::NONE },
        Tile{TileType::W, Action::NONE },
        Tile{TileType::E, Action::NONE }
    };

    const Map m3(2, 3, tiles);
    EXPECT_EQ(m3(0, 0), Tile(TileType::ROAD, Action::ENEMY_NORTH));
    EXPECT_EQ(m3(1, 0), Tile(TileType::BUSH, Action::NONE));
    EXPECT_EQ(m3(0, 1), Tile(TileType::S, Action::NONE));
    EXPECT_EQ(m3(1, 1), Tile(TileType::GRASS, Action::NONE));
    EXPECT_EQ(m3(0, 2), Tile(TileType::W, Action::NONE));
    EXPECT_EQ(m3(1, 2), Tile(TileType::E, Action::NONE));

    EXPECT_THROW(m3(2, 0), util::Exception);
    EXPECT_THROW(m3(0, 3), util::Exception);

    const Map m4(3, 2, tiles);
    EXPECT_EQ(m4(0, 0), Tile(TileType::ROAD, Action::ENEMY_NORTH));
    EXPECT_EQ(m4(1, 0), Tile(TileType::BUSH, Action::NONE));
    EXPECT_EQ(m4(2, 0), Tile(TileType::S, Action::NONE));
    EXPECT_EQ(m4(0, 1), Tile(TileType::GRASS, Action::NONE));
    EXPECT_EQ(m4(1, 1), Tile(TileType::W, Action::NONE));
    EXPECT_EQ(m4(2, 1), Tile(TileType::E, Action::NONE));

    EXPECT_THROW(m4(3, 0), util::Exception);
    EXPECT_THROW(m4(0, 2), util::Exception);
}
}
