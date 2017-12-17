
#include "CCar.h"

#include "util/CException.h"

namespace car {

EOrientation CCar::convert(EDirection direction) {
    switch (direction) {
    case EDirection::NORTH: return EOrientation::NORTH;
    case EDirection::WEST:  return EOrientation::WEST;
    case EDirection::SOUTH: return EOrientation::SOUTH;
    case EDirection::EAST:  return EOrientation::EAST;
    default:                return EOrientation::NORTH;
    }
}

CCar::CCar(EDirection direction)
    : orientation_(convert(direction)),
      direction_(direction),
      nextDirection_(EDirection::NONE) {
    if (not util::isValid(direction)) {
        throw util::CException("CCar - invalid direction", from_EDirection<int>(direction));
    }
}

CCar::~CCar() {
}

void CCar::turn(EDirection direction) {
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

void CCar::stepTurn() {
    const auto finalOrientation = convert(nextDirection_);
    if (finalOrientation == orientation_) {
        return;
    }
    const auto final = from_EOrientation<int>(finalOrientation);
    const auto current = from_EOrientation<int>(orientation_);

    auto stepOrientation = current + signalStep(final, current);

    const auto last = from_EOrientation<int>(EOrientation::LAST);
    if (stepOrientation < 0) {
        stepOrientation += last;
    }

    if (stepOrientation >= last) {
        stepOrientation -= last;
    }

    orientation_ = to_EOrientation(stepOrientation);

    if (orientation_ == finalOrientation) {
        direction_ = nextDirection_;
        nextDirection_ = EDirection::NONE;
    }
}

}
