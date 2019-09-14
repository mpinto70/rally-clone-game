#include "Map.h"

#include "util/Exception.h"

#include <stdexcept>

namespace map {

namespace {
constexpr unsigned MASK_NE = 0b0000'0001;
constexpr unsigned MASK_N = 0b0000'0010;
constexpr unsigned MASK_NW = 0b0000'0100;
constexpr unsigned MASK_W = 0b0000'1000;
constexpr unsigned MASK_SW = 0b0001'0000;
constexpr unsigned MASK_S = 0b0010'0000;
constexpr unsigned MASK_SE = 0b0100'0000;
constexpr unsigned MASK_E = 0b1000'0000;
TileType typeMap[256] = {};

/** \verbatim
             1
      2 ,----------, 0
        |          |
      3 |   tile   | 7
        |          |
      4 `----------' 6
             5
 \endverbatim
 */
void initializeTypeMap() {
    //        ESSS WNNN
    //         E W  W E
    typeMap[0b0000'0000] = TileType::GRASS;
    typeMap[0b0000'0001] = TileType::NE;
    typeMap[0b0000'0010] = TileType::N;
    typeMap[0b0000'0011] = TileType::N;
    typeMap[0b0000'0100] = TileType::NW;
    typeMap[0b0000'0101] = TileType::NE_NW;
    typeMap[0b0000'0110] = TileType::N;
    typeMap[0b0000'0111] = TileType::N;
    typeMap[0b0000'1000] = TileType::W;
    typeMap[0b0000'1001] = TileType::W_NE;
    typeMap[0b0000'1010] = TileType::N_W;
    typeMap[0b0000'1011] = TileType::N_W;
    typeMap[0b0000'1100] = TileType::W;
    typeMap[0b0000'1101] = TileType::W_NE;
    typeMap[0b0000'1110] = TileType::N_W;
    typeMap[0b0000'1111] = TileType::N_W;
    typeMap[0b0001'0000] = TileType::SW;
    typeMap[0b0001'0001] = TileType::NE_SW;
    typeMap[0b0001'0010] = TileType::N_SW;
    typeMap[0b0001'0011] = TileType::N_SW;
    typeMap[0b0001'0100] = TileType::NW_SW;
    typeMap[0b0001'0101] = TileType::NE_NW_SW;
    typeMap[0b0001'0110] = TileType::N_SW;
    typeMap[0b0001'0111] = TileType::N_SW;
    typeMap[0b0001'1000] = TileType::W;
    typeMap[0b0001'1001] = TileType::W_NE;
    typeMap[0b0001'1010] = TileType::N_W;
    typeMap[0b0001'1011] = TileType::N_SW;
    typeMap[0b0001'1100] = TileType::W;
    typeMap[0b0001'1101] = TileType::W_NE;
    typeMap[0b0001'1110] = TileType::N_W;
    typeMap[0b0001'1111] = TileType::N_W;
    typeMap[0b0010'0000] = TileType::S;
    typeMap[0b0010'0001] = TileType::S_NE;
    typeMap[0b0010'0010] = TileType::N_S;
    typeMap[0b0010'0011] = TileType::N_S;
    typeMap[0b0010'0100] = TileType::S_NW;
    typeMap[0b0010'0101] = TileType::S_NE_NW;
    typeMap[0b0010'0110] = TileType::N_S;
    typeMap[0b0010'0111] = TileType::N_S;
    typeMap[0b0010'1000] = TileType::W_S;
    typeMap[0b0010'1001] = TileType::W_S_NE;
    typeMap[0b0010'1010] = TileType::N_W_S;
    typeMap[0b0010'1011] = TileType::N_W_S;
    typeMap[0b0010'1100] = TileType::W_S;
    typeMap[0b0010'1101] = TileType::W_S_NE;
    typeMap[0b0010'1110] = TileType::N_W_S;
    typeMap[0b0010'1111] = TileType::N_W_S;
    typeMap[0b0011'0000] = TileType::S;
    typeMap[0b0011'0001] = TileType::S_NE;
    typeMap[0b0011'0010] = TileType::N_S;
    typeMap[0b0011'0011] = TileType::N_S;
    typeMap[0b0011'0100] = TileType::S_NW;
    typeMap[0b0011'0101] = TileType::S_NE_NW;
    typeMap[0b0011'0110] = TileType::N_S;
    typeMap[0b0011'0111] = TileType::N_S;
    typeMap[0b0011'1000] = TileType::W_S;
    typeMap[0b0011'1001] = TileType::W_S_NE;
    typeMap[0b0011'1010] = TileType::N_W_S;
    typeMap[0b0011'1011] = TileType::N_W_S;
    typeMap[0b0011'1100] = TileType::W_S;
    typeMap[0b0011'1101] = TileType::W_S_NE;
    typeMap[0b0011'1110] = TileType::N_W_S;
    typeMap[0b0011'1111] = TileType::N_W_S;
    typeMap[0b0100'0000] = TileType::SE;
    typeMap[0b0100'0001] = TileType::NE_SE;
    typeMap[0b0100'0010] = TileType::N_SE;
    typeMap[0b0100'0011] = TileType::N_SE;
    typeMap[0b0100'0100] = TileType::NW_SE;
    typeMap[0b0100'0101] = TileType::NE_NW_SE;
    typeMap[0b0100'0110] = TileType::N_SE;
    typeMap[0b0100'0111] = TileType::N_SE;
    typeMap[0b0100'1000] = TileType::W_SE;
    typeMap[0b0100'1001] = TileType::W_NE_SE;
    typeMap[0b0100'1010] = TileType::N_W_SE;
    typeMap[0b0100'1011] = TileType::N_W_SE;
    typeMap[0b0100'1100] = TileType::W_SE;
    typeMap[0b0100'1101] = TileType::W_NE_SE;
    typeMap[0b0100'1110] = TileType::N_W_SE;
    typeMap[0b0100'1111] = TileType::N_W_SE;
    typeMap[0b0101'0000] = TileType::SW_SE;
    typeMap[0b0101'0001] = TileType::NE_SW_SE;
    typeMap[0b0101'0010] = TileType::N_SW_SE;
    typeMap[0b0101'0011] = TileType::N_SW_SE;
    typeMap[0b0101'0100] = TileType::NW_SW_SE;
    typeMap[0b0101'0101] = TileType::NE_NW_SW_SE;
    typeMap[0b0101'0110] = TileType::N_SW_SE;
    typeMap[0b0101'0111] = TileType::N_SW_SE;
    typeMap[0b0101'1000] = TileType::W_SE;
    typeMap[0b0101'1001] = TileType::W_NE_SE;
    typeMap[0b0101'1010] = TileType::N_W_SE;
    typeMap[0b0101'1011] = TileType::N_W_SE;
    typeMap[0b0101'1100] = TileType::W_SE;
    typeMap[0b0101'1101] = TileType::W_NE_SE;
    typeMap[0b0101'1110] = TileType::N_W_SE;
    typeMap[0b0101'1111] = TileType::N_W_SE;
    typeMap[0b0110'0000] = TileType::S;
    typeMap[0b0110'0001] = TileType::S_NE;
    typeMap[0b0110'0010] = TileType::N_S;
    typeMap[0b0110'0011] = TileType::N_S;
    typeMap[0b0110'0100] = TileType::S_NW;
    typeMap[0b0110'0101] = TileType::S_NE_NW;
    typeMap[0b0110'0110] = TileType::N_S;
    typeMap[0b0110'0111] = TileType::N_S;
    typeMap[0b0110'1000] = TileType::W_S;
    typeMap[0b0110'1001] = TileType::W_S_NE;
    typeMap[0b0110'1010] = TileType::N_W_S;
    typeMap[0b0110'1011] = TileType::N_W_S;
    typeMap[0b0110'1100] = TileType::W_S;
    typeMap[0b0110'1101] = TileType::W_S_NE;
    typeMap[0b0110'1110] = TileType::N_W_S;
    typeMap[0b0110'1111] = TileType::N_W_S;
    typeMap[0b0111'0000] = TileType::S;
    typeMap[0b0111'0001] = TileType::S_NE;
    typeMap[0b0111'0010] = TileType::N_S;
    typeMap[0b0111'0011] = TileType::N_S;
    typeMap[0b0111'0100] = TileType::S_NW;
    typeMap[0b0111'0101] = TileType::S_NE_NW;
    typeMap[0b0111'0110] = TileType::N_S;
    typeMap[0b0111'0111] = TileType::N_S;
    typeMap[0b0111'1000] = TileType::W_S;
    typeMap[0b0111'1001] = TileType::W_S_NE;
    typeMap[0b0111'1010] = TileType::N_W_S;
    typeMap[0b0111'1011] = TileType::N_W_S;
    typeMap[0b0111'1100] = TileType::W_S;
    typeMap[0b0111'1101] = TileType::W_S_NE;
    typeMap[0b0111'1110] = TileType::N_W_S;
    typeMap[0b0111'1111] = TileType::N_W_S;
    typeMap[0b1000'0000] = TileType::E;
    typeMap[0b1000'0001] = TileType::E;
    typeMap[0b1000'0010] = TileType::N_E;
    typeMap[0b1000'0011] = TileType::N_E;
    typeMap[0b1000'0100] = TileType::E_NW;
    typeMap[0b1000'0101] = TileType::E_NW;
    typeMap[0b1000'0110] = TileType::N_E;
    typeMap[0b1000'0111] = TileType::N_E;
    typeMap[0b1000'1000] = TileType::W_E;
    typeMap[0b1000'1001] = TileType::W_E;
    typeMap[0b1000'1010] = TileType::N_W_E;
    typeMap[0b1000'1011] = TileType::N_W_E;
    typeMap[0b1000'1100] = TileType::W_E;
    typeMap[0b1000'1101] = TileType::W_E;
    typeMap[0b1000'1110] = TileType::N_W_E;
    typeMap[0b1000'1111] = TileType::N_W_E;
    typeMap[0b1001'0000] = TileType::E_SW;
    typeMap[0b1001'0001] = TileType::E_SW;
    typeMap[0b1001'0010] = TileType::N_E_SW;
    typeMap[0b1001'0011] = TileType::N_E_SW;
    typeMap[0b1001'0100] = TileType::E_NW_SW;
    typeMap[0b1001'0101] = TileType::E_NW_SW;
    typeMap[0b1001'0110] = TileType::N_E_SW;
    typeMap[0b1001'0111] = TileType::N_E_SW;
    typeMap[0b1001'1000] = TileType::W_E;
    typeMap[0b1001'1001] = TileType::W_E;
    typeMap[0b1001'1010] = TileType::N_W_E;
    typeMap[0b1001'1011] = TileType::N_E_SW;
    typeMap[0b1001'1100] = TileType::W_E;
    typeMap[0b1001'1101] = TileType::W_E;
    typeMap[0b1001'1110] = TileType::N_W_E;
    typeMap[0b1001'1111] = TileType::N_W_E;
    typeMap[0b1010'0000] = TileType::S_E;
    typeMap[0b1010'0001] = TileType::S_E;
    typeMap[0b1010'0010] = TileType::N_S_E;
    typeMap[0b1010'0011] = TileType::N_S_E;
    typeMap[0b1010'0100] = TileType::S_E_NW;
    typeMap[0b1010'0101] = TileType::S_E_NW;
    typeMap[0b1010'0110] = TileType::N_S_E;
    typeMap[0b1010'0111] = TileType::N_S_E;
    typeMap[0b1010'1000] = TileType::W_S_E;
    typeMap[0b1010'1001] = TileType::W_S_E;
    typeMap[0b1010'1010] = TileType::N_W_S_E;
    typeMap[0b1010'1011] = TileType::N_W_S_E;
    typeMap[0b1010'1100] = TileType::W_S_E;
    typeMap[0b1010'1101] = TileType::W_S_E;
    typeMap[0b1010'1110] = TileType::N_W_S_E;
    typeMap[0b1010'1111] = TileType::N_W_S_E;
    typeMap[0b1011'0000] = TileType::S_E;
    typeMap[0b1011'0001] = TileType::S_E;
    typeMap[0b1011'0010] = TileType::N_S_E;
    typeMap[0b1011'0011] = TileType::N_S_E;
    typeMap[0b1011'0100] = TileType::S_E_NW;
    typeMap[0b1011'0101] = TileType::S_E_NW;
    typeMap[0b1011'0110] = TileType::N_S_E;
    typeMap[0b1011'0111] = TileType::N_S_E;
    typeMap[0b1011'1000] = TileType::W_S_E;
    typeMap[0b1011'1001] = TileType::W_S_E;
    typeMap[0b1011'1010] = TileType::N_W_S_E;
    typeMap[0b1011'1011] = TileType::N_W_S_E;
    typeMap[0b1011'1100] = TileType::W_S_E;
    typeMap[0b1011'1101] = TileType::W_S_E;
    typeMap[0b1011'1110] = TileType::N_W_S_E;
    typeMap[0b1011'1111] = TileType::N_W_S_E;
    typeMap[0b1100'0000] = TileType::E;
    typeMap[0b1100'0001] = TileType::E;
    typeMap[0b1100'0010] = TileType::N_E;
    typeMap[0b1100'0011] = TileType::N_E;
    typeMap[0b1100'0100] = TileType::E_NW;
    typeMap[0b1100'0101] = TileType::E_NW;
    typeMap[0b1100'0110] = TileType::N_E;
    typeMap[0b1100'0111] = TileType::N_E;
    typeMap[0b1100'1000] = TileType::W_E;
    typeMap[0b1100'1001] = TileType::W_E;
    typeMap[0b1100'1010] = TileType::N_W_E;
    typeMap[0b1100'1011] = TileType::N_W_E;
    typeMap[0b1100'1100] = TileType::W_E;
    typeMap[0b1100'1101] = TileType::W_E;
    typeMap[0b1100'1110] = TileType::N_W_E;
    typeMap[0b1100'1111] = TileType::N_W_E;
    typeMap[0b1101'0000] = TileType::E_SW;
    typeMap[0b1101'0001] = TileType::E_SW;
    typeMap[0b1101'0010] = TileType::N_E_SW;
    typeMap[0b1101'0011] = TileType::N_E_SW;
    typeMap[0b1101'0100] = TileType::E_NW_SW;
    typeMap[0b1101'0101] = TileType::E_NW_SW;
    typeMap[0b1101'0110] = TileType::N_E_SW;
    typeMap[0b1101'0111] = TileType::N_E_SW;
    typeMap[0b1101'1000] = TileType::W_E;
    typeMap[0b1101'1001] = TileType::W_E;
    typeMap[0b1101'1010] = TileType::N_W_E;
    typeMap[0b1101'1011] = TileType::N_W_E;
    typeMap[0b1101'1100] = TileType::W_E;
    typeMap[0b1101'1101] = TileType::W_E;
    typeMap[0b1101'1110] = TileType::N_W_E;
    typeMap[0b1101'1111] = TileType::N_W_E;
    typeMap[0b1110'0000] = TileType::S_E;
    typeMap[0b1110'0001] = TileType::S_E;
    typeMap[0b1110'0010] = TileType::N_S_E;
    typeMap[0b1110'0011] = TileType::N_S_E;
    typeMap[0b1110'0100] = TileType::S_E_NW;
    typeMap[0b1110'0101] = TileType::S_E_NW;
    typeMap[0b1110'0110] = TileType::N_S_E;
    typeMap[0b1110'0111] = TileType::N_S_E;
    typeMap[0b1110'1000] = TileType::W_S_E;
    typeMap[0b1110'1001] = TileType::W_S_E;
    typeMap[0b1110'1010] = TileType::N_W_S_E;
    typeMap[0b1110'1011] = TileType::N_W_S_E;
    typeMap[0b1110'1100] = TileType::W_S_E;
    typeMap[0b1110'1101] = TileType::W_S_E;
    typeMap[0b1110'1110] = TileType::N_W_S_E;
    typeMap[0b1110'1111] = TileType::N_W_S_E;
    typeMap[0b1111'0000] = TileType::S_E;
    typeMap[0b1111'0001] = TileType::S_E;
    typeMap[0b1111'0010] = TileType::N_S_E;
    typeMap[0b1111'0011] = TileType::N_S_E;
    typeMap[0b1111'0100] = TileType::S_E_NW;
    typeMap[0b1111'0101] = TileType::S_E_NW;
    typeMap[0b1111'0110] = TileType::N_S_E;
    typeMap[0b1111'0111] = TileType::N_S_E;
    typeMap[0b1111'1000] = TileType::W_S_E;
    typeMap[0b1111'1001] = TileType::W_S_E;
    typeMap[0b1111'1010] = TileType::N_W_S_E;
    typeMap[0b1111'1011] = TileType::N_W_S_E;
    typeMap[0b1111'1100] = TileType::W_S_E;
    typeMap[0b1111'1101] = TileType::W_S_E;
    typeMap[0b1111'1110] = TileType::N_W_S_E;
    typeMap[0b1111'1111] = TileType::N_W_S_E;
}

TileType getType(unsigned bits) {
    return typeMap[bits];
}
}

Map::Map(const map_dimension_t width,
      const map_dimension_t height,
      const std::vector<Tile>& tiles)
      : width_(width),
        height_(height),
        tiles_(tiles) {
    initializeTypeMap();

    if (width == 0) {
        throw std::invalid_argument("Map - zero width");
    }
    if (height == 0) {
        throw std::invalid_argument("Map - zero height");
    }
    if (tiles.size() != width * height) {
        throw std::invalid_argument("Map - number of tiles ("
                                    + std::to_string(tiles.size())
                                    + ") is not compatible with width X height ("
                                    + std::to_string(width)
                                    + " X "
                                    + std::to_string(height)
                                    + ")");
    }
}

Tile& Map::operator()(const map_dimension_t x, const map_dimension_t y) {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

const Tile& Map::operator()(const map_dimension_t x, const map_dimension_t y) const {
    verifyRange(x, y);
    return tiles_.at(y * width_ + x);
}

void Map::adjustTiles() {
    for (map_dimension_t x = 0; x < width_; ++x) {
        for (map_dimension_t y = 0; y < height_; ++y) {
            auto& tile = operator()(x, y);
            if (tile.type() == TileType::ROAD || tile.type() == TileType::BUSH)
                continue;
            unsigned bits = 0;
            if (y > 0) {
                if (x < width_ - 1 && operator()(x + 1, y - 1).type() == TileType::ROAD) bits += MASK_NE;
                if (operator()(x, y - 1).type() == TileType::ROAD) bits += MASK_N;
                if (x > 0 && operator()(x - 1, y - 1).type() == TileType::ROAD) bits += MASK_NW;
            }
            if (x < width_ - 1 && operator()(x + 1, y).type() == TileType::ROAD) bits += MASK_E;
            if (x > 0 && operator()(x - 1, y).type() == TileType::ROAD) bits += MASK_W;
            if (y < height_ - 1) {
                if (x < width_ - 1 && operator()(x + 1, y + 1).type() == TileType::ROAD) bits += MASK_SE;
                if (operator()(x, y + 1).type() == TileType::ROAD) bits += MASK_S;
                if (x > 0 && operator()(x - 1, y + 1).type() == TileType::ROAD) bits += MASK_SW;
            }
            tile.type(getType(bits));
        }
    }
}

void Map::verifyRange(const map_dimension_t x, const map_dimension_t y) const {
    if (x >= width_)
        throw util::Exception("Map() - horizontal coordinate out of range ("
                                    + std::to_string(x)
                                    + "/"
                                    + std::to_string(width_)
                                    + ")",
              x);
    if (y >= height_)
        throw util::Exception("Map() - vertical coordinate out of range ("
                                    + std::to_string(y)
                                    + "/"
                                    + std::to_string(height_)
                                    + ")",
              y);
}
}
