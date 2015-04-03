#pragma once

#include "map/ETile.h"

#include <allegro.h>
#include <map>
#include <memory>

namespace gamelib {
namespace allegro {

typedef std::unique_ptr<BITMAP, void(*)(BITMAP*)> BITMAP_PTR;

/** Reads the tiles from a file
 * @param fileName      name of the file with the image
 * @param tileWidth     size of each tile
 * @param tileHeight    size of each tile
 * @param gap           gap between, above and below each tile
 * @return the full bitmap and the tiles (sub bitmaps)
 * the expected format of the file is
\verbatim
       |------------------------------image width----------------------------------|
   _ _  ___________________________________________________________________________
    |  |                                                                           |
    |  |     g a p       g a p       g a p       g a p       g a p       g a p     |
    |  |   ,-------,   ,-------,   ,-------,   ,-------,   ,-------,   ,-------,   |---
 image | g |       | g |       | g |       | g |       | g |       | g |       | g |  |
height | a | tile  | a | tile  | a | tile  | a | tile  | a | tile  | a | tile  | a |  | tile
    |  | p |       | p |       | p |       | p |       | p |       | p |       | p |  | height
    |  |   |       |   |       |   |       |   |       |   |       |   |       |   |  |
    |  |   `-------´   `-------´   `-------´   `-------´   `-------´   `-------´   |---
    |  |    g a p        g a p       g a p       g a p       g a p       g a p     |
   _|_ |___________________________________________________________________________|
                                                                        |------|
                                                                          tile
                                                                          width
\endverbatim
 */
class CTileMapper {
    public:
        CTileMapper(const std::string & fileName,
                    unsigned tileWidth,
                    unsigned tileHeight,
                    unsigned gap);
        ~CTileMapper();

        CTileMapper(const CTileMapper &) = delete;
        CTileMapper& operator = (const CTileMapper &) = delete;

        BITMAP * tile(map::ETile tile) const;

        template<typename T>
        BITMAP * tile(T t) const {
            map::ETile tl = map::to_ETile<T>(t);
            return tile(tl);
        }
    private:
        BITMAP_PTR fullBitmap_;
        std::map<map::ETile, BITMAP_PTR> tileMap_;
};
}
}
