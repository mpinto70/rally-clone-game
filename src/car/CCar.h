#pragma once

#include "car/EDirection.h"
#include "car/EOrientation.h"

namespace car {

class CCar {
    public:
        explicit CCar(EDirection direction);
        ~CCar();
        EOrientation orientation() const { return orientation_; }
        EDirection direction() const { return direction_; }
        EDirection nextDirection() const { return nextDirection_; }
        void turn(EDirection direction);
        void stepTurn();
    private:
        EOrientation orientation_;
        EDirection direction_;
        EDirection nextDirection_;
};

}
