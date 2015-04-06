
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

const CTile & CMap::operator()(size_t i, size_t j) const {
    if (i >= width_)
        throw util::CException("CMap() - horizontal coordinate out of range", i);
    if (j >= height_)
        throw util::CException("CMap() - vertical coordinate out of range", j);

    return tiles_.at(j * width_ + i);
}

}
