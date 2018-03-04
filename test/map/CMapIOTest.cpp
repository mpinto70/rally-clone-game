#include "CMapIOTest.h"

#include "map/CMapIO.h"

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <random>
namespace map {

constexpr char tmpFileName[] = "tmp_file_name.map";

void CMapIOTest::TearDown() {
    boost::filesystem::path pathToFile(tmpFileName);
    if (boost::filesystem::exists(pathToFile)) {
        boost::filesystem::remove(pathToFile);
    }
}

TEST_F(CMapIOTest, Read) {
    const CMap map = CMapIO::read(RALLY_ROOT "/test/map/files/map_12_10.map");
    EXPECT_EQ(map.width(), 12u);
    EXPECT_EQ(map.height(), 10u);
    // the first tiles are in sequence
    auto max = static_cast<size_t>(ETileType::LAST);
    const auto& tiles = map.tiles();
    EAction action = EAction::FIRST;
    for (size_t i = 0; i < tiles.size(); ++i) {
        ETileType t = to_ETileType(i % max);
        EXPECT_EQ(tiles[i].type(), t) << i;
        if (tiles[i].type() == ETileType::ROAD) {
            EXPECT_EQ(tiles[i].action(), action) << i;
            const int next_act = from_EAction<int>(action) + 1;
            if (next_act == from_EAction<int>(EAction::LAST))
                action = EAction::FIRST;
            else
                action = to_EAction(next_act);
        } else {
            EXPECT_EQ(tiles[i].action(), EAction::NONE) << i;
        }
    }
}

constexpr auto maxType = static_cast<size_t>(ETileType::LAST) - 1;
constexpr auto maxAction = static_cast<size_t>(EAction::LAST) - 1;
static void verifyWrite(const map_dimension_t width,
      const map_dimension_t height) {
    std::default_random_engine re;
    std::uniform_int_distribution<map_dimension_t> distType{ 0, maxType };
    std::uniform_int_distribution<map_dimension_t> distAction{ 0, maxAction };
    auto diceType = std::bind(distType, re);
    auto diceAction = std::bind(distAction, re);
    const map_dimension_t fullsize = width * height;
    std::vector<CTile> tiles;
    tiles.reserve(fullsize);
    for (size_t i = 0; i < fullsize; ++i) {
        const ETileType type = to_ETileType(diceType());
        const EAction action = (type == ETileType::ROAD) ? to_EAction(diceAction()) : EAction::NONE;
        tiles.emplace_back(type, action);
    }

    const CMap map1(width, height, tiles);
    CMapIO::write(tmpFileName, map1);

    const CMap map2 = CMapIO::read(tmpFileName);

    EXPECT_EQ(map1.width(), map2.width());
    EXPECT_EQ(map1.height(), map2.height());
    EXPECT_EQ(map1.tiles(), map2.tiles());
}

TEST_F(CMapIOTest, Write) {
    verifyWrite(10, 20);
    verifyWrite(200, 100);
}
}
