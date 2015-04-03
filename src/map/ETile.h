#pragma once

#include "util/EUtil.h"
#include <cstdint>
#include <stdexcept>

/** namespaces of elements related to maps. */
namespace map {

typedef std::uint8_t tile_t;
/** Types of tiles. */
enum class ETile : tile_t {
    TOP_LEFT,
    RIGHT_TOP,
    LEFT_BOTTOM,
    BOTTOM_RIGHT,
    GRASS,
    BUSH,
    ROAD,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP,
    LEFT_RIGHT,
    TOP_BOTTOM,
    TOP_LEFT_CORNER,
    RIGHT_TOP_CORNER,
    LEFT_BOTTOM_CORNER,
    BOTTOM_RIGHT_CORNER,
    LEFT_CORNERS,
    TOP_CORNERS,
    BOTTOM_CORNERS,
    RIGHT_CORNERS,
    LAST,
    FIRST = TOP_LEFT
};

template <typename T>
ETile to_ETile(T t) {
    return util::to_Enum<ETile, T>(t);
}

bool operator < (ETile lhs, ETile rhs) {
    return static_cast<tile_t>(lhs) < static_cast<tile_t>(rhs);
}

}

