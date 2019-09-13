#pragma once

#include "util/Util.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace map {

/** the underlying enum type. */
using tile_type_t = std::uint8_t;
/** Types of tiles.
 * TOP, LEFT, RIGHT and BOTTOM refer to the sides
 * NW, SW, SE and NE refer to the corners
 \verbatim
             N
     NW ,----------, NE
        |          |
      W |   tile   | E
        |          |
     SW `----------' SE
             S
 \endverbatim
 */
enum class TileType : tile_type_t {
    ROAD,
    N_W,
    N,
    N_E,
    N_W_SE,
    N_W_E,
    N_E_SW,
    W,
    GRASS,
    E,
    N_W_BOTTOM,
    NE_NW_SW_SE,
    S_E_TOP,
    N_W_S_E,
    W_S,
    S,
    S_E,
    W_S_NE,
    W_S_E,
    S_E_NW,
    BUSH,
    W_E,
    N_S,
    N_SW_SE,
    W_NE_SE,
    S_NE_NW,
    E_NW_SW,
    NE_NW,
    NW_SW,
    SW_SE,
    NE_SE,
    NE,
    NW,
    SW,
    SE,
    NE_NW_SW,
    NE_NW_SE,
    NE_SW_SE,
    NW_SW_SE,
    NW_SE,
    NE_SW,
    LAST,
    FIRST = ROAD
};

static_assert(static_cast<int>(TileType::LAST) == 41);
/** convert a value of type \b T to a ETile value.
 * @param t the value to be converted
 */
template <typename T>
TileType to_ETileType(T t) {
    return util::to_Enum<TileType, T>(t);
}

/** convert a value of type ETile to a value of type \b T.
 * @param enum_value the value to be converted
 */
template <typename T>
T from_ETileType(TileType enum_value) {
    return util::from_Enum<T, TileType>(enum_value);
}

/** converts enum value to string
 * @param enum_value the value to be converted
 */
std::string to_string(TileType enum_value);
}
