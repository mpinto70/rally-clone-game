#pragma once

#include <type_traits>

/** namespace of elements related to maps. */
namespace map {

/** generic comparator for enum values
 * @param lhs left hand operand
 * @param rhs right hand operand
 */
template <typename ENUM>
bool operator<(ENUM lhs, ENUM rhs) {
    using enum_type = typename std::underlying_type<ENUM>::type;
    return static_cast<enum_type>(lhs) < static_cast<enum_type>(rhs);
}
}
