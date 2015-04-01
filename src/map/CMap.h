#pragma once

#include "map/ETile.h"
#include <cstddef>
#include <vector>

namespace map {

class CMap {
    public:
        CMap(size_t width,
             size_t height,
             const std::vector<ETile> & tiles);

        CMap(const CMap &) = delete;

        size_t height() const { return height_; }

        size_t width() const { return width_; }

        const std::vector<ETile>& tiles() const { return tiles_; }

    private:
        size_t width_;
        size_t height_;
        std::vector<ETile> tiles_;
};

}
