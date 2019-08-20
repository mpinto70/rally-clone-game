#pragma once

#include "map/Action.h"
#include "map/TileType.h"

namespace map {

/** represents a single tile in the map. */
class Tile {
public:
    /** creates the object.
     * @param type the type of the tile
     * @param action the action in the tile
     */
    explicit Tile(TileType type, Action action = Action::NONE);

    /** returns the type of the tile. */
    [[nodiscard]] TileType type() const { return type_; }
    /** returns the action in the tile. */
    [[nodiscard]] Action action() const { return action_; }
    /** set the type and adjust action if necessary. */
    void type(TileType type);
    /** returns the action in the tile. */
    void action(Action action);

private:
    TileType type_; ///< tile type
    Action action_; ///< tile action
};

[[nodiscard]] bool operator==(const Tile& lhs, const Tile& rhs);
}
