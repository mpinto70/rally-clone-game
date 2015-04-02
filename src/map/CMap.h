#pragma once

#include "map/ETile.h"
#include <cstddef>
#include <vector>

namespace map {

/** represents a full map. */
class CMap {
    public:
        /** creates the object.
         * @param width map width
         * @param height map height
         * @param tiles map tiles
         */
        CMap(size_t width,
             size_t height,
             const std::vector<ETile> & tiles);

        /** shall not be copied. */
        CMap(const CMap &) = delete;

        /** returns the height. */
        size_t height() const { return height_; }

        /** returns the width. */
        size_t width() const { return width_; }

        /** returns the tiles. */
        const std::vector<ETile>& tiles() const { return tiles_; }

    private:
        size_t width_;              ///< width
        size_t height_;             ///< height
        std::vector<ETile> tiles_;  ///< tiles
};

}