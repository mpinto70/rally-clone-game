#include "MiniMapMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

MiniMapMapper createMiniMapMapper(const BITMAP_PTR& fullImage) {
    constexpr unsigned MINI_TILE_SIZE = 48;
    constexpr unsigned X = 576;
    constexpr unsigned Y = 144;

    return MiniMapMapper(fullImage, MINI_TILE_SIZE, MINI_TILE_SIZE, X, Y, 4, 1);
}
}
}
}
