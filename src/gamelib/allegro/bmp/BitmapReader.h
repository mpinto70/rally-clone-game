#pragma once

#include "gamelib/allegro/AllegroUtil.h"

#include <allegro.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace gamelib {
namespace allegro {
namespace bmp {

class BitmapReader {
public:
    using tiles_t = std::pair<BITMAP_PTR, std::vector<BITMAP_PTR>>;
    /** Reads the bitmap and sub-bitmaps from a file
     * @param fileName      name of the file with the image
     * @param tileWidth     size of each sub-bitmap
     * @param tileHeight    size of each sub-bitmap
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
         |  |   `-------�   `-------�   `-------�   `-------�   `-------�   `-------�   |---
         |  |    g a p        g a p       g a p       g a p       g a p       g a p     |
        _|_ |___________________________________________________________________________|
                                                                             |------|
                                                                               tile
                                                                               width
     \endverbatim
     */
    static tiles_t readBmps(const std::string& fileName,
          const unsigned tileWidth,
          const unsigned tileHeight,
          const unsigned gap);
};
}
}
}
