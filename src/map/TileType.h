#pragma once

#include "util/Util.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
using tile_type_t = std::uint8_t;
/** Types of tiles. */
enum class TileType : tile_type_t {
    ROAD,
    TOP_LEFT,
    TOP,
    RIGHT_TOP,
    TILE_4,
    TILE_5,
    TILE_6,
    IGNORED_1,
    LEFT,
    GRASS,
    RIGHT,
    TILE_11,
    TILE_12,
    TILE_13,
    IGNORED_2,
    LEFT_BOTTOM,
    BOTTOM,
    BOTTOM_RIGHT,
    TILE_18,
    TILE_19,
    TILE_20,
    BUSH,
    IGNORED_3,
    IGNORED_4,
    TILE_24,
    TILE_25,
    TILE_26,
    TILE_27,
    LAST,
    FIRST = ROAD
};

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
