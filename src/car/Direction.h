#pragma once

#include "util/Util.h"

#include <cstdint>
#include <stdexcept>

namespace car {

/** the underlying enum type. */
using direction_t = std::uint8_t;
/** car directions. */
enum class Direction : direction_t {
    NONE,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    LAST,
    FIRST = NONE
};

/** convert a value of type \b T to a EDirection value.
 * @param t the value to be converted
 */
template <typename T>
Direction to_Direction(T t) {
    return util::to_Enum<Direction, T>(t);
}

/** convert a value of type EDirection to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_Direction(Direction enum_value) {
    return util::from_Enum<T, Direction>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(Direction enum_value);
}
