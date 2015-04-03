
#include "CTileMapper.h"

#include "util/CEnumIterator.h"
#include "util/CException.h"

#include <string>
#include <type_traits>
#include <vector>

namespace gamelib {
namespace allegro {
namespace bmp {

CTileMapper::CTileMapper(const std::string & fileName,
                         unsigned tileWidth,
                         unsigned tileHeight,
                         const unsigned gap)
    : fullBitmap_(nullptr, destroy_bitmap) {
    auto tiles = CBitmapReader::readTiles(fileName, tileWidth, tileHeight, gap);
    fullBitmap_.swap(tiles.first);
    using map::ETile;
    using map::tile_t;

    const auto qttyRead = tiles.second.size();
    const auto qttyExpected = static_cast<tile_t>(ETile::LAST);
    if (qttyRead != qttyExpected) {
        throw util::CException("CTileMapper - number of tiles read ("
                               + std::to_string(qttyRead)
                               + ") differs from the expected ("
                               + std::to_string(qttyExpected)
                               + ") in "
                               + fileName
                               , 1);
    }
    for (auto tile : util::CEnumIterator<ETile>()) {
        const auto index = static_cast<tile_t>(tile);
        tileMap_.insert(std::make_pair(tile, std::move(tiles.second.at(index))));
    }
}

CTileMapper::~CTileMapper() {
    tileMap_.clear();
    fullBitmap_.reset();
}

BITMAP * CTileMapper::tile(map::ETile tile) const {
    const auto it = tileMap_.find(tile);
    if (it == tileMap_.end())
        return nullptr;
    else return it->second.get();
}

}
}
}
