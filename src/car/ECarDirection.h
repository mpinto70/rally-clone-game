#pragma once

#include "util/EUtil.h"

#include <cstdint>
#include <stdexcept>

namespace car {

/** the underlying enum type. */
typedef std::uint8_t car_direction_t;
/** car directions. */
enum class ECarDirection : car_direction_t {
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

/** convert a value of type \b T to a ECarDirection value.
 * @param t the value to be converted
 */
template <typename T>
ECarDirection to_ECarDirection(T t) {
    return util::to_Enum<T, ECarDirection>(t);
}

/** convert a value of type ECarDirection to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_ECarDirection(ECarDirection enum_value) {
    return util::from_Enum<T, ECarDirection>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(ECarDirection enum_value);

}
