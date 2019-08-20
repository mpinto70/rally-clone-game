#include "Tile.h"

#include "util/Exception.h"
#include "util/Util.h"

namespace map {

Tile::Tile(TileType type, Action action)
      : type_(type), action_(action) {
    if (action_ != Action::NONE && type_ != TileType::ROAD) {
        throw util::Exception("Tile - incompatible type "
                                    + to_string(type_)
                                    + " and action "
                                    + to_string(action_),
              1);
    }
}

bool operator==(const Tile& lhs, const Tile& rhs) {
    return lhs.type() == rhs.type()
           && lhs.action() == rhs.action();
}

void Tile::type(TileType type) {
    type_ = type;
    if (type_ != TileType::ROAD) {
        action_ = Action::NONE;
    }
}

void Tile::action(Action action) {
    if (action != Action::NONE
          && type_ != TileType::ROAD)
        throw util::Exception("Tile::action(action) - incompatible type "
                                    + to_string(type_)
                                    + " and new action "
                                    + to_string(action),
              1);
    action_ = action;
}
}
