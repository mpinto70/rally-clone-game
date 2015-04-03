#include "CTileReader.h"

#include "util/CException.h"

namespace gamelib {
namespace allegro {

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

CTileReader::tiles_t CTileReader::readTiles(const std::string& fileName,
                                            const unsigned tileWidth,
                                            const unsigned tileHeight,
                                            const unsigned gap) {
    BITMAP * fullBitmap = load_bitmap(fileName.c_str(), nullptr);

    if (fullBitmap == nullptr)
        throw util::CException("CTileReader - it was not possible to read the tiles from " + fileName, 1);

    const unsigned w = fullBitmap->w;
    const unsigned h = fullBitmap->h;

    if ((w - gap) % (tileWidth + gap) != 0) {
        destroy_bitmap(fullBitmap);
        throw util::CException("CTileReader - the image width ("
                               + std::to_string(w)
                               + ") is incompatible with tile size ("
                               + std::to_string(tileWidth)
                               + ") and gap size ("
                               + std::to_string(gap)
                               + ") for "
                               + fileName, 2);
    }
    if (h != gap + tileHeight + gap) {
        destroy_bitmap(fullBitmap);
        throw util::CException("CTileReader - the image height ("
                               + std::to_string(h)
                               + ") is incompatible with tile size ("
                               + std::to_string(tileWidth)
                               + ") and gap size ("
                               + std::to_string(gap)
                               + ") for "
                               + fileName, 3);
    }

    const unsigned qttyTiles = (w - gap) / (tileWidth + gap);
    std::vector<BITMAP *> tiles(qttyTiles, nullptr);
    for (unsigned i = 0; i < qttyTiles; ++i) {
        const unsigned x = (tileWidth + gap) * i + gap;
        // a subbitmap that shares parent bitmap's memory.
        BITMAP * sub = create_sub_bitmap(fullBitmap, x, gap, tileWidth, tileHeight);
        if (sub == nullptr) {
            destroy_bitmap(fullBitmap);
            throw util::CException("CTileReader - it was not possible to reference the sub tile at ["
                                   + std::to_string(x)
                                   + ","
                                   + std::to_string(gap)
                                   + "] for "
                                   + fileName, 4);
        }
        tiles[i] = sub;
    }

    return std::make_pair(fullBitmap, tiles);
}

}
}

