#pragma once

#include "map/CTile.h"
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
             const std::vector<CTile> & tiles);

        /** returns the height. */
        size_t height() const { return height_; }

        /** returns the width. */
        size_t width() const { return width_; }

        /** returns the tiles. */
        const std::vector<CTile>& tiles() const { return tiles_; }

        CTile & operator()(size_t x,
                           size_t y);
        const CTile & operator()(size_t x,
                                 size_t y) const;

    private:
        size_t width_;              ///< width
        size_t height_;             ///< height
        std::vector<CTile> tiles_;  ///< tiles

        void verifyRange(size_t x,
                         size_t y) const;
};

}
