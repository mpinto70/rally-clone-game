
#include "CCar.h"

#include "util/CException.h"

namespace car {

static EOrientation convert(EDirection direction) {
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
    if (not util::isValid(direction))
        throw util::CException("CCar - invalid direction", from_EDirection<int>(direction));
}

CCar::~CCar() {
}

void CCar::turn(EDirection direction) {
    nextDirection_ = direction;
}

}
