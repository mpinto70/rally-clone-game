#pragma once

#include "map/ETile.h"
#include "map/EAction.h"

namespace map {

class CTile {
    public:
        CTile(ETile type,
              EAction action);
        ~CTile();

        ETile tile() const { return type_; }
        EAction action() const { return action_; }
    private:
        ETile type_;
        EAction action_;
};

}
