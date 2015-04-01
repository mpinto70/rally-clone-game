#pragma once

#include <cstdint>

namespace map {
/** Responsible for time lapse garantee. */
enum class ETile : std::uint8_t {
    ROAD,
    GRASS,
    BUSH,
    TOP,
    LEFT,
    BOTTOM,
    RIGHT,
    TOP_LEFT,
    LEFT_BOTTOM,
    BOTTOM_RIGHT,
    RIGHT_TOP,
    LEFT_RIGHT,
    TOP_BOTTOM,
    TOP_LEFT_CORNER,
    LEFT_BOTTOM_CORNER,
    BOTTOM_RIGHT_CORNER,
    RIGHT_TOP_CORNER,
    TOP_CORNERS,
    LEFT_CORNERS,
    BOTTOM_CORNERS,
    RIGHT_CORNERS
};

}

