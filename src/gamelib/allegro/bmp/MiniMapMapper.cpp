#include "MiniMapMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

MiniMapMapper createMiniMapMapper(const std::string& file_name) {
    constexpr unsigned TILE_SIZE = 16 * SIZE_MULTIPLIER;
    constexpr unsigned X = 192 * SIZE_MULTIPLIER;
    constexpr unsigned Y = 48 * SIZE_MULTIPLIER;

    return MiniMapMapper(file_name, TILE_SIZE, TILE_SIZE, X, Y, 4, 1);
}
}
}
}
