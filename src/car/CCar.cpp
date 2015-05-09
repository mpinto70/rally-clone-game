
#include "CCar.h"

namespace car {

CCar::CCar(EOrientation orientation,
           EDirection direction)
    : orientation_(orientation),
      direction_(direction),
      nextDirection_(EDirection::NONE) {
}

CCar::~CCar() {
}

}
