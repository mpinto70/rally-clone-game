#pragma once

#include "map/ETileType.h"
#include "map/EAction.h"

namespace map {

/** represents a single tile in the map. */
class CTile {
    public:
        /** creates the object.
         * @param type the type of the tile
         * @param action the action in the tile
         */
        explicit CTile(ETileType type,
                       EAction action = EAction::NONE);
        /** destroys the object. */
        ~CTile();

        /** returns the type of the tile. */
        ETileType type() const { return type_; }
        /** returns the action in the tile. */
        EAction action() const { return action_; }
        /** set the type and adjust action if necessary. */
        void type(ETileType type);
        /** returns the action in the tile. */
        void action(EAction action);
private:
        ETileType type_;        ///< tile type
        EAction action_;    ///< tile action
};

bool operator == (const CTile & lhs, const CTile & rhs);
}
