#pragma once

#include "map/EMapUtil.h"
#include "util/EUtil.h"
#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
typedef std::uint8_t action_t;
/** Types of actions. */
enum class EAction : action_t {
    NONE,
    CREATE_ENEMY,
    CREATE_STONE,
    LAST,
    FIRST = NONE
};

/** convert a value of type \b T to a EAction value.
 * @param t the value to be converted
 */
template <typename T>
EAction to_EAction(T t) {
    return util::to_Enum<EAction, T>(t);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(EAction enum_value);

}

