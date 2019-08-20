#include "Map.h"

#include "util/Exception.h"

#include <stdexcept>

namespace map {

Map::Map(const map_dimension_t width,
      const map_dimension_t height,
      const std::vector<Tile>& tiles)
      : width_(width),
        height_(height),
        tiles_(tiles) {
    if (width == 0) {
        throw std::invalid_argument("Map - zero width");
    }
    if (height == 0) {
        throw std::invalid_argument("Map - zero height");
    }
    if (tiles.size() != width * height) {
        throw std::invalid_argument("Map - number of tiles ("
                                    + std::to_string(tiles.size())
                                    + ") is not compatible with width X height ("
                                    + std::to_string(width)
                                    + " X "
                                    + std::to_string(height)
                                    + ")");
    }
}

Tile& Map::operator()(const map_dimension_t x, const map_dimension_t y) {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

const Tile& Map::operator()(const map_dimension_t x, const map_dimension_t y) const {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

void Map::verifyRange(const map_dimension_t x, const map_dimension_t y) const {
    if (x >= width_)
        throw util::Exception("Map() - horizontal coordinate out of range ("
                                    + std::to_string(x)
                                    + "/"
                                    + std::to_string(width_)
                                    + ")",
              x);
    if (y >= height_)
        throw util::Exception("Map() - vertical coordinate out of range ("
                                    + std::to_string(y)
                                    + "/"
                                    + std::to_string(height_)
                                    + ")",
              y);
}
}
