#include "MiniMapMapper.h"

namespace gamelib {
namespace allegro {
namespace bmp {

MiniMapMapper createMiniMapMapper(const std::string& file_name) {
    constexpr unsigned TILE_SIZE = 48;
    constexpr unsigned X = 576;
    constexpr unsigned Y = 144;

    return MiniMapMapper(file_name, TILE_SIZE, TILE_SIZE, X, Y, 4, 1);
}
}
}
}
