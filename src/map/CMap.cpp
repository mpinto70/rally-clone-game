
#include "CMap.h"

#include <stdexcept>

namespace map {

CMap::CMap(const size_t width,
           const size_t height,
           const std::vector<ETile>& tiles)
    : width_(width),
      height_(height),
      tiles_(tiles) {
    if (width == 0) {
        throw std::invalid_argument("CMap - zero width");
    }
    if (height == 0) {
        throw std::invalid_argument("CMap - zero height");
    }
    if (tiles.size() != width * height) {
        throw std::invalid_argument("CMap - number of tiles ("
                                    + std::to_string(tiles.size())
                                    + ") is not compatible with width X height ("
                                    + std::to_string(width)
                                    + " X "
                                    + std::to_string(height)
                                    + ")");
    }
}

}
