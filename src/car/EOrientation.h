#pragma once

#include "util/EUtil.h"

#include <cstdint>
#include <stdexcept>

namespace car {

/** the underlying enum type. */
typedef std::uint8_t direction_t;
/** car directions. */
enum class EOrientation : direction_t {
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
EOrientation to_EOrientation(T t) {
    return util::to_Enum<T, EOrientation>(t);
}

/** convert a value of type EOrientation to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_EOrientation(EOrientation enum_value) {
    return util::from_Enum<T, EOrientation>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(EOrientation enum_value);

}
