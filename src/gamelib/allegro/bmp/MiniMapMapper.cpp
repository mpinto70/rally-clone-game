#include "MiniMapMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

MiniMapMapper createMiniMapMapper(BITMAP_PTR& fullImage) {
    constexpr unsigned TILE_SIZE = 48;
    constexpr unsigned X = 576;
    constexpr unsigned Y = 144;

    return MiniMapMapper(fullImage, TILE_SIZE, TILE_SIZE, X, Y, 4, 1);
}
}
}
}
