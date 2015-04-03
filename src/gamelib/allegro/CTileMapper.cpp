
#include "CTileMapper.h"

#include "gamelib/allegro/CTileReader.h"
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
    const auto tiles = CTileReader::readTiles(fileName, tileSize, tileSize, gap);
    using map::ETile;
    using map::tile_t;

    const auto qttyRead = tiles.second.size();
    const auto qttyExpected = static_cast<tile_t>(ETile::LAST);
    if (qttyRead != qttyExpected) {
        destroy_bitmap(tiles.first);
        throw util::CException("CTileMapper - number of tiles read ("
                               + std::to_string(qttyRead)
                               + ") differs from the expected ("
                               + std::to_string(qttyExpected)
                               + ") in "
                               + fileName
                               , 1);
    }
    tileSet_ = tiles.first;
    for (auto tile : util::CEnumIterator<ETile>()) {
        const auto index = static_cast<tile_t>(tile);
        tileMap_[tile] = tiles.second.at(index);
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
