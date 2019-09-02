#pragma once

#include "util/Util.h"

#include <cstdint>

namespace fuel {

/** the underlying enum type. */
using fuel_t = std::uint8_t;
/** car directions. */
enum class Type : fuel_t {
    FUEL,
    FUEL_S,
    FUEL_L,
    LAST,
    FIRST = FUEL
};

/** convert a value of type \b T to a EFuel value.
 * @param t the value to be converted
 */
template <typename T>
Type to_Fuel(T t) {
    return util::to_Enum<Type, T>(t);
}

/** convert a value of type EFuel to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
constexpr T from_Fuel(Type enum_value) {
    return util::from_Enum<T, Type>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(Type enum_value);

}
