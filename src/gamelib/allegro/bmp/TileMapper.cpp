#include "TileMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {
namespace {
enum class FileTileType {
    ROAD,
    N_W,
    N,
    N_E,
    N_W_SE,
    N_W_E,
    N_E_SW,
    IGNORED_1,
    W,
    GRASS,
    E,
    N_W_BOTTOM,
    NE_NW_SW_SE,
    S_E_TOP,
    N_W_S_E,
    W_S,
    S,
    S_E,
    W_S_NE,
    W_S_E,
    S_E_NW,
    BUSH,
    W_E,
    N_S,
    N_SW_SE,
    W_NE_SE,
    S_NE_NW,
    E_NW_SW,
    NE_NW,
    NW_SW,
    SW_SE,
    NE_SE,
    NE,
    NW,
    SW,
    SE,
    NE_NW_SW,
    NE_NW_SE,
    NE_SW_SE,
    NW_SW_SE,
    NW_SE,
    NE_SW,
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
