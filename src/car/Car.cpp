
#include "Car.h"

#include "../util/Exception.h"

namespace car {

Orientation Car::convert(Direction direction) {
    switch (direction) {
        case Direction::NORTH: return Orientation::NORTH;
        case Direction::WEST: return Orientation::WEST;
        case Direction::SOUTH: return Orientation::SOUTH;
        case Direction::EAST: return Orientation::EAST;
        default: return Orientation::NORTH;
    }
}

Car::Car(Direction direction)
      : orientation_(convert(direction)),
        direction_(direction),
        nextDirection_(Direction::NONE) {
    if (not util::isValid(direction)) {
        throw util::Exception("Car - invalid direction", from_Direction<int>(direction));
    }
}

Car::~Car() {
}

void Car::turn(Direction direction) {
    nextDirection_ = direction;
}

static int signalStep(const int final,
      const int current) {
    const auto distance = final - current;
    const auto absDistance = abs(distance);
    if (absDistance <= 6) {
        if (distance < 0) {
            return -1;
        } else {
            return 1;
        }
    } else {
        if (distance < 0) {
            return 1;
        } else {
            return -1;
        }
    }
}

void Car::stepTurn() {
    const auto finalOrientation = convert(nextDirection_);
    if (finalOrientation == orientation_) {
        return;
    }
    const auto final = from_Orientation<int>(finalOrientation);
    const auto current = from_Orientation<int>(orientation_);

    auto stepOrientation = current + signalStep(final, current);

    const auto last = from_Orientation<int>(Orientation::LAST);
    if (stepOrientation < 0) {
        stepOrientation += last;
    }

    if (stepOrientation >= last) {
        stepOrientation -= last;
    }

    orientation_ = to_Orientation(stepOrientation);

    if (orientation_ == finalOrientation) {
        direction_ = nextDirection_;
        nextDirection_ = Direction::NONE;
    }
}
}
