#include "SpriteReader.h"

#include "util/Exception.h"

namespace gamelib {
namespace allegro {
namespace bmp {

SpriteReader::sprites_t SpriteReader::readImages(const std::string& fileName,
      unsigned spriteWidth,
      unsigned spriteHeight,
      unsigned leftFirst,
      unsigned topFirst,
      unsigned numColumns,
      unsigned numRows) {
    BITMAP_PTR fullBitmap(load_bitmap(fileName.c_str(), nullptr), destroy_bitmap);

    if (fullBitmap == nullptr) {
        throw util::Exception("SpriteReader - it was not possible to read the sprites from " + fileName, 1);
    }

    const unsigned w = fullBitmap->w;
    const unsigned h = fullBitmap->h;

    if (w < leftFirst + numColumns * spriteWidth) {
        throw util::Exception("SpriteReader - the image width ("
                                    + std::to_string(w)
                                    + ") is incompatible with sprite width ("
                                    + std::to_string(spriteWidth)
                                    + "), left of first sprite  ("
                                    + std::to_string(leftFirst)
                                    + ") and number of columns  ("
                                    + std::to_string(numColumns)
                                    + ") for "
                                    + fileName,
              2);
    }
    if (w < leftFirst + numColumns * spriteWidth) {
        throw util::Exception("SpriteReader - the image height ("
                                    + std::to_string(h)
                                    + ") is incompatible with sprite height ("
                                    + std::to_string(spriteHeight)
                                    + "), top of first sprite  ("
                                    + std::to_string(topFirst)
                                    + ") and number of rows  ("
                                    + std::to_string(numRows)
                                    + ") for "
                                    + fileName,
              3);
    }

    std::vector<BITMAP_PTR> sprites;
    for (unsigned r = 0, y = topFirst; r < numRows; ++r, y += spriteHeight) {
        for (unsigned c = 0, x = leftFirst; c < numColumns; ++c, x += spriteWidth) {
            BITMAP* sub = create_sub_bitmap(fullBitmap.get(), x, y, spriteWidth, spriteHeight);
            if (sub == nullptr) {
                throw util::Exception("SpriteReader - it was not possible to reference the sub sprite at ["
                                            + std::to_string(x)
                                            + ","
                                            + std::to_string(y)
                                            + "] for "
                                            + fileName,
                      4);
            }
            sprites.emplace_back(sub, destroy_bitmap);
        }
    }

    return std::make_pair(std::move(fullBitmap), std::move(sprites));
}
}
}
}