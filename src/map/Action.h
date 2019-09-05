#pragma once

#include "map/MapUtil.h"
#include "util/Util.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
using action_t = std::uint8_t;
/** Types of actions. */
enum class Action : action_t {
    NONE,
    ENEMY_NORTH,
    ENEMY_EAST,
    ENEMY_SOUTH,
    ENEMY_WEST,
    BANG,
    STONE_1,
    STONE_2,
    SMOKE,
    FUEL,
    FUEL_S,
    FUEL_L,
    LAST,
    FIRST = NONE
};

/** convert a value of type \b T to a EAction value.
 * @param t the value to be converted
 */
template <typename T>
Action to_EAction(T t) {
    return util::to_Enum<Action, T>(t);
}

/** convert a value of type EAction to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_EAction(Action enum_value) {
    return util::from_Enum<T, Action>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(Action enum_value);
}
