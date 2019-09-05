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
      unsigned numRows,
      unsigned gapX,
      unsigned gapY) {
    auto fullBitmap = readFullImage(fileName);
    auto sprites = readImages(fullBitmap, spriteWidth, spriteHeight, leftFirst, topFirst, numColumns, numRows, gapX, gapY);
    return std::make_pair(std::move(fullBitmap), std::move(sprites));
}

BITMAP_PTR SpriteReader::readFullImage(const std::string& fileName) {
    BITMAP_PTR fullBitmap(al_load_bitmap(fileName.c_str()), al_destroy_bitmap);

    if (fullBitmap == nullptr) {
        throw util::Exception("SpriteReader - it was not possible to read the sprites from " + fileName, 1);
    }

    return fullBitmap;
}

std::vector<BITMAP_PTR> SpriteReader::readImages(BITMAP_PTR& fullBitmap,
      unsigned spriteWidth,
      unsigned spriteHeight,
      unsigned leftFirst,
      unsigned topFirst,
      unsigned numColumns,
      unsigned numRows,
      unsigned gapX,
      unsigned gapY) {
    const unsigned w = al_get_bitmap_width(fullBitmap.get());
    const unsigned h = al_get_bitmap_height(fullBitmap.get());

    if (w < leftFirst + numColumns * (spriteWidth + gapX) - gapX) {
        throw util::Exception("SpriteReader - the image width ("
                                    + std::to_string(w)
                                    + ") is incompatible with sprite width ("
                                    + std::to_string(spriteWidth)
                                    + "), left of first sprite  ("
                                    + std::to_string(leftFirst)
                                    + ") and number of columns  ("
                                    + std::to_string(numColumns)
                                    + ")",
              2);
    }
    if (h < topFirst + numRows * (spriteHeight + gapY) - gapY) {
        throw util::Exception("SpriteReader - the image height ("
                                    + std::to_string(h)
                                    + ") is incompatible with sprite height ("
                                    + std::to_string(spriteHeight)
                                    + "), top of first sprite  ("
                                    + std::to_string(topFirst)
                                    + ") and number of rows  ("
                                    + std::to_string(numRows)
                                    + ")",
              3);
    }

    std::vector<BITMAP_PTR> sprites;
    for (unsigned r = 0, y = topFirst; r < numRows; ++r, y += spriteHeight + gapY) {
        for (unsigned c = 0, x = leftFirst; c < numColumns; ++c, x += spriteWidth + gapX) {
            ALLEGRO_BITMAP* sub = al_create_sub_bitmap(fullBitmap.get(), x, y, spriteWidth, spriteHeight);
            if (sub == nullptr) {
                throw util::Exception("SpriteReader - it was not possible to reference the sub sprite at ["
                                            + std::to_string(x)
                                            + ","
                                            + std::to_string(y)
                                            + "]",
                      4);
            }
            sprites.emplace_back(sub, al_destroy_bitmap);
        }
    }

    return sprites;
}
}
}
}
