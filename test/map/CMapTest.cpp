#include "map/CMap.h"
#include "util/CException.h"

#include <gtest/gtest.h>

namespace map {

TEST(CMapTest, Creation) {
    std::vector<CTile> tiles = {
        CTile{ ETileType::ROAD, EAction::STONE },
        CTile{ ETileType::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    EXPECT_EQ(m1.width(), 1u);
    EXPECT_EQ(m1.height(), 2u);
    EXPECT_EQ(m1.tiles(), tiles);

    tiles = {
        CTile{ ETileType::ROAD, EAction::ENEMY_NORTH },
        CTile{ ETileType::BUSH, EAction::NONE },
        CTile{ ETileType::BOTTOM, EAction::NONE },
        CTile{ ETileType::GRASS, EAction::NONE },
        CTile{ ETileType::LEFT, EAction::NONE },
        CTile{ ETileType::RIGHT, EAction::NONE }
    };

    const CMap m2(2, 3, tiles);
    EXPECT_EQ(m2.width(), 2u);
    EXPECT_EQ(m2.height(), 3u);
    EXPECT_EQ(m2.tiles(), tiles);
}

TEST(CMapTest, InvalidCreation) {
    EXPECT_THROW(CMap(0, 2, { CTile{ ETileType::ROAD, EAction::STONE }, CTile{ ETileType::BUSH, EAction::NONE } }),
          std::invalid_argument);

    EXPECT_THROW(CMap(1, 0, { CTile{ ETileType::ROAD, EAction::STONE }, CTile{ ETileType::BUSH, EAction::NONE } }),
          std::invalid_argument);

    EXPECT_THROW(CMap(1, 3, { CTile{ ETileType::ROAD, EAction::STONE }, CTile{ ETileType::BUSH, EAction::NONE } }),
          std::invalid_argument);
}

TEST(CMapTest, Indexing) {
    std::vector<CTile> tiles = {
        CTile{ ETileType::ROAD, EAction::STONE },
        CTile{ ETileType::BUSH, EAction::NONE }
    };

    const CMap m1(1, 2, tiles);
    EXPECT_EQ(m1(0, 0), CTile(ETileType::ROAD, EAction::STONE));
    EXPECT_EQ(m1(0, 1), CTile(ETileType::BUSH, EAction::NONE));
    EXPECT_THROW(m1(1, 0),
          util::CException);
    EXPECT_THROW(m1(0, 2),
          util::CException);

    const CMap m2(2, 1, tiles);
    EXPECT_EQ(m2(0, 0), CTile(ETileType::ROAD, EAction::STONE));
    EXPECT_EQ(m2(1, 0), CTile(ETileType::BUSH, EAction::NONE));
    EXPECT_THROW(m2(2, 0), util::CException);
    EXPECT_THROW(m2(0, 1), util::CException);

    tiles = {
        CTile{ ETileType::ROAD, EAction::ENEMY_NORTH },
        CTile{ ETileType::BUSH, EAction::NONE },
        CTile{ ETileType::BOTTOM, EAction::NONE },
        CTile{ ETileType::GRASS, EAction::NONE },
        CTile{ ETileType::LEFT, EAction::NONE },
        CTile{ ETileType::RIGHT, EAction::NONE }
    };

    const CMap m3(2, 3, tiles);
    EXPECT_EQ(m3(0, 0), CTile(ETileType::ROAD, EAction::ENEMY_NORTH));
    EXPECT_EQ(m3(1, 0), CTile(ETileType::BUSH, EAction::NONE));
    EXPECT_EQ(m3(0, 1), CTile(ETileType::BOTTOM, EAction::NONE));
    EXPECT_EQ(m3(1, 1), CTile(ETileType::GRASS, EAction::NONE));
    EXPECT_EQ(m3(0, 2), CTile(ETileType::LEFT, EAction::NONE));
    EXPECT_EQ(m3(1, 2), CTile(ETileType::RIGHT, EAction::NONE));

    EXPECT_THROW(m3(2, 0), util::CException);
    EXPECT_THROW(m3(0, 3), util::CException);

    const CMap m4(3, 2, tiles);
    EXPECT_EQ(m4(0, 0), CTile(ETileType::ROAD, EAction::ENEMY_NORTH));
    EXPECT_EQ(m4(1, 0), CTile(ETileType::BUSH, EAction::NONE));
    EXPECT_EQ(m4(2, 0), CTile(ETileType::BOTTOM, EAction::NONE));
    EXPECT_EQ(m4(0, 1), CTile(ETileType::GRASS, EAction::NONE));
    EXPECT_EQ(m4(1, 1), CTile(ETileType::LEFT, EAction::NONE));
    EXPECT_EQ(m4(2, 1), CTile(ETileType::RIGHT, EAction::NONE));

    EXPECT_THROW(m4(3, 0), util::CException);
    EXPECT_THROW(m4(0, 2), util::CException);
}
}
