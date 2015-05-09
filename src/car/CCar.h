#pragma once

#include "car/EDirection.h"
#include "car/EOrientation.h"

namespace car {

class CCar {
    public:
        CCar(EOrientation orientation,
             EDirection direction);
        ~CCar();
        EOrientation orientation() const { return orientation_; }
        EDirection direction() const { return direction_; }
        EDirection nextDirection() const { return nextDirection_; }
    private:
        EOrientation orientation_;
        EDirection direction_;
        EDirection nextDirection_;
};

}
