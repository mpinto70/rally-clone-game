#pragma once

#include "util/EUtil.h"

#include <cstdint>
#include <stdexcept>

namespace car {

/** the underlying enum type. */
typedef std::uint8_t direction_t;
/** car directions. */
enum class EDirection : direction_t {
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
EDirection to_EDirection(T t) {
    return util::to_Enum<EDirection, T>(t);
}

/** convert a value of type EDirection to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_EDirection(EDirection enum_value) {
    return util::from_Enum<T, EDirection>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(EDirection enum_value);

}
