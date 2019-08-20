#pragma once

#include "car/Direction.h"
#include "car/Orientation.h"

namespace car {

class Car {
public:
    static Orientation convert(Direction direction);
    explicit Car(Direction direction);
    [[nodiscard]] Orientation orientation() const { return orientation_; }
    [[nodiscard]] Direction direction() const { return direction_; }
    [[nodiscard]] Direction nextDirection() const { return nextDirection_; }
    void turn(Direction direction);
    void stepTurn();

private:
    Orientation orientation_;
    Direction direction_;
    Direction nextDirection_;
};
}
