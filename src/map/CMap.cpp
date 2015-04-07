
#include "CMap.h"

#include "util/CException.h"
#include <stdexcept>

namespace map {

CMap::CMap(const size_t width,
           const size_t height,
           const std::vector<CTile>& tiles)
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

CTile& CMap::operator()(size_t x,
                        size_t y) {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

const CTile & CMap::operator()(size_t x,
                               size_t y) const {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

void CMap::verifyRange(size_t x,
                       size_t y) const {
    if (x >= width_)
        throw util::CException("CMap() - horizontal coordinate out of range ("
                               + std::to_string(x)
                               + "/"
                               + std::to_string(width_)
                               + ")"
                               , x);
    if (y >= height_)
        throw util::CException("CMap() - vertical coordinate out of range ("
                               + std::to_string(y)
                               + "/"
                               + std::to_string(height_)
                               + ")"
                               , y);
}

}
