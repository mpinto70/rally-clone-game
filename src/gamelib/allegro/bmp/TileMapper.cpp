#include "TileMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {
namespace {
enum class FileTileType {
    ROAD,
    TOP_LEFT,
    TOP,
    RIGHT_TOP,
    TOP_LEFT_SE,
    RIGHT_TOP_LEFT,
    RIGHT_TOP_SW,
    IGNORED_1,
    LEFT,
    GRASS,
    RIGHT,
    TOP_LEFT_BOTTOM,
    NW_SW_SE_NE,
    BOTTOM_RIGHT_TOP,
    TOP_LEFT_RIGHT_BOTTOM,
    LEFT_BOTTOM,
    BOTTOM,
    BOTTOM_RIGHT,
    LEFT_BOTTOM_NE,
    LEFT_BOTTOM_RIGHT,
    BOTTOM_RIGHT_NW,
    BUSH,
    LEFT_RIGHT,
    TOP_BOTTOM,
    TOP_SW_SE,
    LEFT_SE_NE,
    BOTTOM_NE_NW,
    RIGHT_NW_SW,
    POINTS_01,
    POINTS_02,
    POINTS_03,
    POINTS_04,
    POINTS_05,
    POINTS_06,
    POINTS_07,
    POINTS_08,
    POINTS_09,
    POINTS_10,
    POINTS_11,
    POINTS_12,
    POINTS_13,
    POINTS_14,
    LAST,
    FIRST = ROAD
};
}

TileMapper::TileMapper(const BITMAP_PTR& fullImage,
      const unsigned leftFirst,
      const unsigned topFirst) {
    const auto tile_size = imageHeight(0);
    auto sprites = SpriteReader::readImages(fullImage, tile_size, tile_size, leftFirst, topFirst, 7, 6);
    sprites.erase(sprites.begin() + static_cast<size_t>(FileTileType::IGNORED_1));
    for (auto e : util::EnumIterator<map::TileType>()) {
        const auto idx = map::from_ETileType<size_t>(e);
        spriteMap_.insert({ e, std::move(sprites[idx]) });
    }
}

TileMapper createTileMapper(const BITMAP_PTR& fullImage, TileSource type) {
    constexpr unsigned TILE_SIZE = 72;
    constexpr unsigned NUM_COLUMNS = 7;
    constexpr unsigned NUM_LINES = 6;
    constexpr unsigned FIRST_LINE_Y = 336;

    const auto idx = util::from_Enum<unsigned>(type);
    const auto x0 = (idx % 2) * TILE_SIZE * NUM_COLUMNS;
    const auto y0 = (idx / 2) * TILE_SIZE * NUM_LINES + FIRST_LINE_Y;
    return TileMapper(fullImage, x0, y0);
}

std::string to_string(TileSource enum_value) {
    switch (enum_value) {
        CASE_ENUM_TO_STRING(TileSource::GREEN);
        CASE_ENUM_TO_STRING(TileSource::PINK);
        CASE_ENUM_TO_STRING(TileSource::BROWN);
        CASE_ENUM_TO_STRING(TileSource::BLUE);
        CASE_ENUM_TO_STRING(TileSource::GRAY);
        CASE_ENUM_TO_STRING(TileSource::ORANGE);
        CASE_ENUM_TO_STRING(TileSource::LIGHT_GRAY);
        CASE_ENUM_TO_STRING(TileSource::LIGHT_GREEN);
        case TileSource::LAST:
            break;
    }
    throw util::Exception("to_string(TileSource) - invalid argument", util::from_Enum<int>(enum_value));
}
}
}
}
