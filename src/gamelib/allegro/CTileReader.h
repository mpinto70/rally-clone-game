#pragma once

#include <allegro.h>
#include <vector>
#include <string>

namespace gamelib {
namespace allegro {

class CTileReader {
    public:
        CTileReader() = delete;
        ~CTileReader() = delete;
        typedef std::pair<BITMAP*, std::vector<BITMAP *>> tiles_t;
        static tiles_t readTiles(const std::string & fileName,
                                 unsigned tileWidth,
                                 unsigned tileHeight,
                                 unsigned gap);
};

}
}
