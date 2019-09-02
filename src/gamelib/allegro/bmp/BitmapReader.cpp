#include "BitmapReader.h"

#include "util/Exception.h"

namespace gamelib {
namespace allegro {
namespace bmp {

BitmapReader::tiles_t BitmapReader::readImages(const std::string& fileName,
      const unsigned tileWidth,
      const unsigned tileHeight,
      const unsigned gap) {
    BITMAP_PTR fullBitmap(al_load_bitmap(fileName.c_str()), al_destroy_bitmap);

    if (fullBitmap == nullptr) {
        throw util::Exception("TileReader - it was not possible to read the tiles from " + fileName, 1);
    }

    const unsigned w = al_get_bitmap_width(fullBitmap.get());
    const unsigned h = al_get_bitmap_height(fullBitmap.get());

    if ((w - gap) % (tileWidth + gap) != 0) {
        throw util::Exception("TileReader - the image width ("
                                    + std::to_string(w)
                                    + ") is incompatible with tile size ("
                                    + std::to_string(tileWidth)
                                    + ") and gap size ("
                                    + std::to_string(gap)
                                    + ") for "
                                    + fileName,
              2);
    }
    if (h != gap + tileHeight + gap) {
        throw util::Exception("TileReader - the image height ("
                                    + std::to_string(h)
                                    + ") is incompatible with tile size ("
                                    + std::to_string(tileWidth)
                                    + ") and gap size ("
                                    + std::to_string(gap)
                                    + ") for "
                                    + fileName,
              3);
    }

    const unsigned qttyTiles = (w - gap) / (tileWidth + gap);
    std::vector<BITMAP_PTR> tiles;
    tiles.reserve(qttyTiles);
    for (unsigned i = 0; i < qttyTiles; ++i) {
        const unsigned x = (tileWidth + gap) * i + gap;
        // a subbitmap that shares parent bitmap's memory.
        ALLEGRO_BITMAP* sub = al_create_sub_bitmap(fullBitmap.get(), x, gap, tileWidth, tileHeight);
        if (sub == nullptr) {
            throw util::Exception("TileReader - it was not possible to reference the sub tile at ["
                                        + std::to_string(x)
                                        + ","
                                        + std::to_string(gap)
                                        + "] for "
                                        + fileName,
                  4);
        }
        tiles.emplace_back(sub, al_destroy_bitmap);
    }

    return std::make_pair(std::move(fullBitmap), std::move(tiles));
}
}
}
}
