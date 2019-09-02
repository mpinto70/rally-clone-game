#pragma once

#include "util/Util.h"

#include <cstdint>

namespace minimap {

/** the underlying enum type. */
using minimap_t = std::uint8_t;
/** car directions. */
enum class Type : minimap_t {
    PLAYER_ON,
    PLAYER_OFF,
    FUEL,
    ENEMY,
    LAST,
    FIRST = PLAYER_ON
};

/** convert a value of type \b T to a Type value.
 * @param t the value to be converted
 */
template <typename T>
Type to_MiniMap(T t) {
    return util::to_Enum<Type, T>(t);
}

/** convert a value of type Type to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
constexpr T from_MiniMap(Type enum_value) {
    return util::from_Enum<T, Type>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(Type enum_value);

}
