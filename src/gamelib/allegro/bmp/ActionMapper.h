#pragma once

#include "gamelib/allegro/bmp/SpriteMapper.h"
#include "map/Action.h"

namespace gamelib {
namespace allegro {
namespace bmp {

using ActionMapper = SpriteMapper<map::Action>;

ActionMapper createActionMapper(const std::string& file_name);
}
}
}
