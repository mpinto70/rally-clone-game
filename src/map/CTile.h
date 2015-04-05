#pragma once

#include "map/ETile.h"
#include "map/EAction.h"

namespace map {

class CTile {
    public:
        explicit CTile(ETile type,
                       EAction action = EAction::NONE);
        ~CTile();

        ETile type() const { return type_; }
        EAction action() const { return action_; }
    private:
        ETile type_;
        EAction action_;
};

}
