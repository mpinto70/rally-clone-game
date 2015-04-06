#pragma once

#include "util/EUtil.h"
#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
typedef std::uint8_t tile_type_t;
/** Types of tiles. */
enum class ETileType : tile_type_t {
    TOP_LEFT,
    RIGHT_TOP,
    LEFT_BOTTOM,
    BOTTOM_RIGHT,
    GRASS,
    BUSH,
    ROAD,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP,
    LEFT_RIGHT,
    TOP_BOTTOM,
    TOP_LEFT_CORNER,
    RIGHT_TOP_CORNER,
    LEFT_BOTTOM_CORNER,
    BOTTOM_RIGHT_CORNER,
    LEFT_CORNERS,
    TOP_CORNERS,
    BOTTOM_CORNERS,
    RIGHT_CORNERS,
    LAST,
    FIRST = TOP_LEFT
};

/** convert a value of type \b T to a ETile value.
 * @param t the value to be converted
 */
template <typename T>
ETileType to_ETile(T t) {
    return util::to_Enum<ETileType, T>(t);
}

/** convert a value of type ETile to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_ETile(ETileType enum_value) {
    return util::from_Enum<T, ETileType>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(ETileType enum_value);

}

