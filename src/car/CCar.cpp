
#include "CCar.h"

#include "util/CException.h"

namespace car {

CCar::CCar(EOrientation orientation,
           EDirection direction)
    : orientation_(orientation),
      direction_(direction),
      nextDirection_(EDirection::NONE) {
    if (not util::isValid(orientation))
        throw util::CException("CCar - invalid orientation", from_EOrientation<int>(orientation));
    if (not util::isValid(direction))
        throw util::CException("CCar - invalid direction", from_EDirection<int>(direction));
}

CCar::~CCar() {
}

}
