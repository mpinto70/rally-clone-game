#pragma once

#include "util/EUtil.h"

#include <cstdint>
#include <stdexcept>

/** namespaces of elements related to maps. */
namespace map {

typedef std::uint8_t car_direction_t;
/** Directions of cars. */
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

template <typename T>
ECarDirection to_ECarDirection(T t) {
    return util::to_Enum<T, ECarDirection>(t);
}

bool operator < (ECarDirection lhs, ECarDirection rhs) {
    return static_cast<car_direction_t>(lhs) < static_cast<car_direction_t>(rhs);
}

}
