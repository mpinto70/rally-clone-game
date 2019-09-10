#pragma once

#include "gamelib/allegro/AllegroUtil.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace gamelib {
namespace allegro {
namespace bmp {

class SpriteReader {
public:
    using sprites_t = std::pair<BITMAP_PTR, std::vector<BITMAP_PTR>>;

    static BITMAP_PTR readFullImage(const std::string& fileName);

    /** Reads the sprites from a bitmap image file
     * @param fileName      name of the file with the image
     * @param spriteWidth   size of each sprite
     * @param spriteHeight  size of each sprite
     * @param leftFirst     X coordinate of first sprite
     * @param topFirst      Y coordinate of first sprite
     * @param numColumns    number of sprite columns
     * @param numRows       number of sprite rows
     * @return the full bitmap and the sprites
     * the expected format of the file is
     \verbatim
                |------------------------image width-------------------------------|
           -,-- +------------------------------------------------------------------+ ---------,-
         Y  |   |                                                                  |          |
           -'-- |  ,--------,--------,--------,--------,--------,--------,         | --       |
                |  |        |        |        |        |        |        |         |  |       |
                |  | sprite | sprite | sprite | sprite | sprite | sprite |         | sprite   |
                |  |        |        |        |        |        |        |         | height   |
                |  |        |        |        |        |        |        |         |  |       |
                |  :--------:--------:--------:--------:--------:--------'         | --       |
                |  |        |        |        |        |        |        |         |          |
                |  | sprite | sprite | sprite | sprite | sprite | sprite |         |        image
                |  |        |        |        |        |        |        |         |        height
                |  |        |        |        |        |        |        |         |          |
                |  :--------:--------:--------:--------:--------:--------'         |          |
                |  |        |        |        |        |        |        |         |          |
                |  | sprite | sprite | sprite | sprite | sprite | sprite |         |          |
                |  |        |        |        |        |        |        |         |          |
                |  |        |        |        |        |        |        |         |          |
                |  `--------'--------`--------`--------`--------`--------'         |          |
                |                                                                  |          |
                |--,--------------------------------------------,--------,---------' ---------'-
                |--|                                            |-sprite-|
                 X                                                width


     \endverbatim
     */
    static sprites_t readImages(const std::string& fileName,
          unsigned spriteWidth,
          unsigned spriteHeight,
          unsigned leftFirst,
          unsigned topFirst,
          unsigned numColumns,
          unsigned numRows,
          unsigned gapX = 0,
          unsigned gapY = 0);

    static std::vector<BITMAP_PTR> readImages(BITMAP_PTR& fullImage,
          unsigned spriteWidth,
          unsigned spriteHeight,
          unsigned leftFirst,
          unsigned topFirst,
          unsigned numColumns,
          unsigned numRows,
          unsigned gapX = 0,
          unsigned gapY = 0);
};
}
}
}
