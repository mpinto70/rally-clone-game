#pragma once

#include "gamelib/allegro/CBitmapReader.h"
#include "map/ETile.h"

#include <allegro.h>
#include <map>
#include <memory>

namespace gamelib {
namespace allegro {

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
        std::map<map::ETile, BITMAP_PTR> tileMap_;
        BITMAP_PTR fullBitmap_;
};
}
}
