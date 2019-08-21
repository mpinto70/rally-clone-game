#pragma once

#include "map/Tile.h"

#include <cstddef>
#include <vector>

namespace map {

using map_dimension_t = std::uint32_t;

/** represents a full map. */
class Map {
public:
    /** creates the object.
     * @param width map width
     * @param height map height
     * @param tiles map tiles
     */
    Map(map_dimension_t width,
          map_dimension_t height,
          const std::vector<Tile>& tiles);

    /** returns the height. */
    [[nodiscard]] map_dimension_t height() const { return height_; }

    /** returns the width. */
    [[nodiscard]] map_dimension_t width() const { return width_; }

    /** returns the tiles. */
    [[nodiscard]] const std::vector<Tile>& tiles() const { return tiles_; }

    /** return the tile at column \b x and line \b y.
     * @param x the horizontal coordinate of the tile
     * @param y the vertical coordinate of the tile
     */
    Tile& operator()(map_dimension_t x, map_dimension_t y);
    /** return the tile at column \b x and line \b y.
     * @param x the horizontal coordinate of the tile
     * @param y the vertical coordinate of the tile
     */
    const Tile& operator()(map_dimension_t x, map_dimension_t y) const;

private:
    map_dimension_t width_;   ///< width
    map_dimension_t height_;  ///< height
    std::vector<Tile> tiles_; ///< tiles

    void verifyRange(map_dimension_t x,
          map_dimension_t y) const;
};
}
