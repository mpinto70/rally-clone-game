#pragma once

#include "gamelib/allegro/bmp/SpriteMapper.h"
#include "minimap/MiniMap.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using MiniMapMapper = SpriteMapper<minimap::Type>;

MiniMapMapper createMiniMapMapper(const BITMAP_PTR& fullImage);
}
}
}
