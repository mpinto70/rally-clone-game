
#pragma once

#include <type_traits>

namespace map {

#define CASE_ENUM_TO_STRING(VALUE) case VALUE: return #VALUE
template<typename ENUM>
bool operator < (ENUM lhs, ENUM rhs) {
    typedef typename std::underlying_type<ENUM>::type enum_type;
    return static_cast<enum_type>(lhs) < static_cast<enum_type>(rhs);
}

}
