
#include "testCMapIO.h"

#include "map/CMapIO.h"

#include <boost/filesystem.hpp>

#include <random>
#include <iostream>
namespace map {

constexpr char tmpFileName[] = "tmp_file_name.map";

void testCMapIO::tearDown() {
    boost::filesystem::path pathToFile(tmpFileName);
    if (boost::filesystem::exists(pathToFile)) {
        boost::filesystem::remove(pathToFile);
    }
}

void testCMapIO::testRead() {
    const CMap map = CMapIO::read("./files/map_12_10.map");
    TS_ASSERT_EQUALS(map.width(), 12u);
    TS_ASSERT_EQUALS(map.height(), 10u);
    // the first tiles are in sequence
    auto max = static_cast<size_t>(ETile::LAST);
    const auto & tiles = map.tiles();
    EAction action = EAction::FIRST;
    for (size_t i = 0; i < tiles.size(); ++i) {
        ETile t = to_ETile(i % max);
        TSM_ASSERT_EQUALS(i, tiles[i].type(), t);
        if (tiles[i].type() == ETile::ROAD) {
            TSM_ASSERT_EQUALS(i, tiles[i].action(), action);
            const int next_act = from_EAction<int>(action) + 1;
            if (next_act == from_EAction<int>(EAction::LAST))
                action = EAction::FIRST;
            else
                action = to_EAction(next_act);
        } else {
            TSM_ASSERT_EQUALS(i, tiles[i].action(), EAction::NONE);
        }
    }
}

constexpr auto maxType = static_cast<size_t>(ETile::LAST) - 1;
constexpr auto maxAction = static_cast<size_t>(EAction::LAST) - 1;
static void verifyWrite(const size_t width,
                        const size_t height) {
    std::default_random_engine re;
    std::uniform_int_distribution<size_t> distType{0, maxType};
    std::uniform_int_distribution<size_t> distAction{0, maxAction};
    auto diceType = std::bind(distType, re);
    auto diceAction = std::bind(distAction, re);
    const size_t fullsize = width * height;
    std::vector<CTile> tiles;
    tiles.reserve(fullsize);
    for (size_t i = 0; i < fullsize; ++i) {
        const ETile type = to_ETile(diceType());
        const EAction action = (type == ETile::ROAD) ? to_EAction(diceAction()) : EAction::NONE;
        tiles.emplace_back(type, action);
    }

    const CMap map1(width, height, tiles);
    CMapIO::write(tmpFileName, map1);

    const CMap map2 = CMapIO::read(tmpFileName);

    TS_ASSERT_EQUALS(map1.width(), map2.width());
    TS_ASSERT_EQUALS(map1.height(), map2.height());
    TS_ASSERT_EQUALS(map1.tiles(), map2.tiles());
}

void testCMapIO::testWrite() {
    verifyWrite(10, 20);
    verifyWrite(200, 100);
}

}

