
#pragma once

#include <type_traits>

/** namespaces of elements related to maps. */
namespace map {

/** generic comparator for enum values
 * @param lhs left hand operand
 * @param rhs right hand operanda
 */
template <typename ENUM>
bool operator<(ENUM lhs, ENUM rhs) {
    typedef typename std::underlying_type<ENUM>::type enum_type;
    return static_cast<enum_type>(lhs) < static_cast<enum_type>(rhs);
}
}
