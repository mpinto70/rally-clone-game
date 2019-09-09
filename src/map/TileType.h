#pragma once

#include "util/Util.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
using tile_type_t = std::uint8_t;
/** Types of tiles.
 * TOP, LEFT, RIGHT and BOTTOM refer to the sides
 * NW, SW, SE and NE refer to the corners
 \verbatim
             top
     NW ,-----------, NE
        |           |
      l |           | r
      e |           | i
      f |   tile    | g
      t |           | h
        |           | t
        |           |
     SW `-----------' SE
            bottom
 \endverbatim
 */
enum class TileType : tile_type_t {
    ROAD,
    TOP_LEFT,
    TOP,
    RIGHT_TOP,
    TOP_LEFT_SE,
    RIGHT_TOP_LEFT,
    RIGHT_TOP_SW,
    LEFT,
    GRASS,
    RIGHT,
    TOP_LEFT_BOTTOM,
    NW_SW_SE_NE,
    BOTTOM_RIGHT_TOP,
    TOP_LEFT_RIGHT_BOTTOM,
    LEFT_BOTTOM,
    BOTTOM,
    BOTTOM_RIGHT,
    LEFT_BOTTOM_NE,
    LEFT_BOTTOM_RIGHT,
    BOTTOM_RIGHT_NW,
    BUSH,
    LEFT_RIGHT,
    TOP_BOTTOM,
    TOP_SW_SE,
    LEFT_SE_NE,
    BOTTOM_NE_NW,
    RIGHT_NW_SW,
    NE_NW,
    NW_SW,
    SW_SE,
    SE_NE,
    NE,
    NW,
    SW,
    SE,
    NE_NW_SW,
    SE_NE_NW,
    SW_SE_NE,
    NW_SW_SE,
    NW_SE,
    NE_SW,
    LAST,
    FIRST = ROAD
};

static_assert(static_cast<int>(TileType::LAST) == 41);
/** convert a value of type \b T to a ETile value.
 * @param t the value to be converted
 */
template <typename T>
TileType to_ETileType(T t) {
    return util::to_Enum<TileType, T>(t);
}

/** convert a value of type ETile to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_ETileType(TileType enum_value) {
    return util::from_Enum<T, TileType>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(TileType enum_value);
}
