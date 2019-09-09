#include "MapIOTest.h"
#include "map/MapIO.h"

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <sstream>

namespace map {

constexpr char tmpFileName[] = "tmp_file_name.map";

void MapIOTest::TearDown() {
    boost::filesystem::path pathToFile(tmpFileName);
    if (boost::filesystem::exists(pathToFile)) {
        boost::filesystem::remove(pathToFile);
    }
}

namespace {
Map create_map(const uint32_t width, const uint32_t height) {
    std::vector<Tile> tiles;
    tiles.reserve(width * height);
    uint32_t j = 0;
    const auto max_type = from_ETileType<uint32_t>(TileType::LAST);
    const auto max_action = from_EAction<uint32_t>(Action::LAST);
    for (size_t i = 0; i < width * height; ++i) {
        const TileType tileType = to_ETileType(i % max_type);
        const Action action = (tileType == TileType::ROAD) ? to_EAction(++j % max_action) : Action::NONE;
        tiles.emplace_back(tileType, action);
    }
    return Map(width, height, tiles);
}
}

TEST_F(MapIOTest, WriteRead) {
    const Map map = create_map(120, 157);
    std::ostringstream out;
    MapIO::write(out, map);
    std::istringstream in(out.str());
    const Map readMap = MapIO::read(in);

    EXPECT_EQ(map.width(), readMap.width());
    EXPECT_EQ(map.height(), readMap.height());
    EXPECT_EQ(map.tiles(), readMap.tiles());
}
}
