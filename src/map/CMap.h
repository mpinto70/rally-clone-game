#pragma once

#include "map/CTile.h"
#include <cstddef>
#include <vector>

namespace map {

typedef std::uint32_t map_dimension_t;

/** represents a full map. */
class CMap {
    public:
        /** creates the object.
         * @param width map width
         * @param height map height
         * @param tiles map tiles
         */
        CMap(map_dimension_t width,
             map_dimension_t height,
             const std::vector<CTile> & tiles);

        /** returns the height. */
        map_dimension_t height() const { return height_; }

        /** returns the width. */
        map_dimension_t width() const { return width_; }

        /** returns the tiles. */
        const std::vector<CTile>& tiles() const { return tiles_; }

        CTile & operator()(map_dimension_t x,
                           map_dimension_t y);
        const CTile & operator()(map_dimension_t x,
                                 map_dimension_t y) const;

    private:
        map_dimension_t width_;              ///< width
        map_dimension_t height_;             ///< height
        std::vector<CTile> tiles_;  ///< tiles

        void verifyRange(map_dimension_t x,
                         map_dimension_t y) const;
};

}
