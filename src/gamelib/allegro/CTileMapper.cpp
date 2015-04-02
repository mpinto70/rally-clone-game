
#include "CTileMapper.h"

#include "util/CEnumIterator.h"
#include "util/CException.h"

#include <string>
#include <type_traits>

namespace gamelib {
namespace allegro {

CTileMapper::CTileMapper(const std::string & fileName,
                         const unsigned tileSize,
                         const unsigned gap)
    : tileSet_(nullptr) {
    using map::ETile;
    using map::tile_t;
    tileSet_ = load_bitmap(fileName.c_str(), nullptr);

    if (tileSet_ == nullptr)
        throw util::CException("CTileMapper - it was not possible to read the tiles from " + fileName, 1);

    const unsigned w = tileSet_->w;
    const unsigned h = tileSet_->h;

    const auto qttyTiles = static_cast<tile_t>(ETile::LAST);
    if (w != qttyTiles * (tileSize + gap) + gap)
        throw util::CException("CTileMapper - the image width ("
                               + std::to_string(w)
                               + ") is incompatible with tile size ("
                               + std::to_string(tileSize)
                               + ") and gap size ("
                               + std::to_string(gap)
                               + ") for "
                               + fileName, 2);
    if (h != gap + tileSize + gap)
        throw util::CException("CTileMapper - the image height ("
                               + std::to_string(h)
                               + ") is incompatible with tile size ("
                               + std::to_string(tileSize)
                               + ") and gap size ("
                               + std::to_string(gap)
                               + ") for "
                               + fileName, 3);

    for (auto tile : util::CEnumIterator<ETile>()) {
        const unsigned x = (tileSize + gap) * ((tile_t) tile) + gap;
        // a subbitmap that shares parent bitmap's memory.
        BITMAP * sub = create_sub_bitmap(tileSet_, x, gap, tileSize, tileSize);
        if (sub == nullptr)
            throw util::CException("CTileMapper - it was not possible to reference the sub tile at ["
                                   + std::to_string(x)
                                   + ","
                                   + std::to_string(gap)
                                   + "] for "
                                   + fileName, 4);
        tileMap_[tile] = sub;
    }
}

CTileMapper::~CTileMapper() {
    if (tileSet_) {
        destroy_bitmap(tileSet_);
    }
}

BITMAP * CTileMapper::tile(map::ETile tile) const {
    const auto it = tileMap_.find(tile);
    if (it == tileMap_.end())
        return nullptr;
    else return it->second;
}

}
}
