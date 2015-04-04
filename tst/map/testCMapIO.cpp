
#include "testCMapIO.h"

#include "map/CMapIO.h"

#include <boost/filesystem.hpp>

#include <random>
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
    for (size_t i = 0; i < tiles.size(); ++i) {
        ETile t = util::to_Enum<ETile>(i % max);
        TSM_ASSERT_EQUALS(i, tiles[i], t);
    }
}

constexpr auto maxTile = static_cast<size_t>(ETile::LAST) - 1;
static void verifyWrite(const size_t width,
                        const size_t height) {
    std::default_random_engine re;
    std::uniform_int_distribution<size_t> dist{0, maxTile};
    auto dice = std::bind(dist, re);
    const size_t fullsize = width * height;
    std::vector<ETile> tiles(fullsize, ETile::GRASS);
    for (size_t i = 0; i < fullsize; ++i) {
        tiles[i] = util::to_Enum<ETile>(dice());
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

