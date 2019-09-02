#include "TileMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

TileMapper createTileMapper(const std::string& file_name, TileSource type) {
    constexpr unsigned TILE_SIZE = 24 * SIZE_MULTIPLIER;
    constexpr unsigned NUM_COLUMNS = 7;
    constexpr unsigned NUM_LINES = 4;
    constexpr unsigned FIRST_LINE_Y = 112 * SIZE_MULTIPLIER;

    const auto idx = util::from_Enum<unsigned>(type);
    const auto x0 = (idx % 2) * TILE_SIZE * NUM_COLUMNS;
    const auto y0 = (idx / 2) * TILE_SIZE * NUM_LINES + FIRST_LINE_Y;
    return TileMapper(file_name, TILE_SIZE, TILE_SIZE, x0, y0, NUM_COLUMNS, NUM_LINES);
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
