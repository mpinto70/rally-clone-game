#pragma once

#include "map/ETile.h"

#include <allegro.h>
#include <map>

namespace gamelib {
namespace allegro {

class CTileMapper {
    public:
        CTileMapper(const std::string & fileName,
                    unsigned tileSize,
                    unsigned gap);
        ~CTileMapper();

        CTileMapper(const CTileMapper &) = delete;
        CTileMapper& operator = (const CTileMapper &) = delete;

        BITMAP * tile(map::ETile tile) const;

        template<typename T>
        BITMAP * tile(T t) const {
            map::ETile tl = map::convertToETile(t);
            return tile(tl);
        }
    private:
        BITMAP * tileSet_;
        std::map<map::ETile, BITMAP*> tileMap_;
};
}
}
