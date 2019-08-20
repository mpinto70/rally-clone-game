#pragma once

#include "util/Util.h"

#include <cstdint>
#include <stdexcept>

namespace car {

/** the underlying enum type. */
using orientation_t = std::uint8_t;
/** car directions. */
enum class Orientation : orientation_t {
    NORTH,
    NORTH_EAST,
    EAST_NORTH,
    EAST,
    EAST_SOUTH,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST_SOUTH,
    WEST,
    WEST_NORTH,
    NORTH_WEST,
    LAST,
    FIRST = NORTH
};

/** convert a value of type \b T to a EOrientation value.
 * @param t the value to be converted
 */
template <typename T>
Orientation to_Orientation(T t) {
    return util::to_Enum<Orientation, T>(t);
}

/** convert a value of type EOrientation to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
constexpr T from_Orientation(Orientation enum_value) {
    return util::from_Enum<T, Orientation>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(Orientation enum_value);
}
