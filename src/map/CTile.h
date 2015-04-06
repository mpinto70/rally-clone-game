#pragma once

#include "map/ETile.h"
#include "map/EAction.h"

namespace map {

/** represents a single tile in the map. */
class CTile {
    public:
        /** creates the object.
         * @param type the type of the tile
         * @param action the action in the tile
         */
        explicit CTile(ETile type,
                       EAction action = EAction::NONE);
        /** destroys the object. */
        ~CTile();

        /** returns the type of the tile. */
        ETile type() const { return type_; }
        /** returns the action in the tile. */
        EAction action() const { return action_; }
    private:
        ETile type_;        ///< tile type
        EAction action_;    ///< tile action
};

bool operator == (const CTile & lhs, const CTile & rhs);
}
