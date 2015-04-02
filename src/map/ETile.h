#pragma once

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
    constexpr T first = static_cast<T>(ETile::FIRST);
    constexpr T last = static_cast<T>(ETile::LAST);
    if (t < first || t >= last) {
        throw std::invalid_argument("convertToETile - out of range (" + std::to_string(t) + ")");
    }
    return static_cast<ETile>(t);
}

bool operator < (ETile lhs, ETile rhs) {
    return static_cast<tile_t>(lhs) < static_cast<tile_t>(rhs);
}

}

