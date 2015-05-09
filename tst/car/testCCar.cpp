
#include "testCCar.h"

#include "car/CCar.h"
#include "util/CException.h"

namespace car {

void testCCar::testCreation() {
    const CCar c1(EOrientation::EAST_NORTH, EDirection::NORTH);
    TS_ASSERT_EQUALS(c1.orientation(), EOrientation::EAST_NORTH);
    TS_ASSERT_EQUALS(c1.direction(), EDirection::NORTH);
    TS_ASSERT_EQUALS(c1.nextDirection(), EDirection::NONE);

    const CCar c2(EOrientation::SOUTH, EDirection::EAST);
    TS_ASSERT_EQUALS(c2.orientation(), EOrientation::SOUTH);
    TS_ASSERT_EQUALS(c2.direction(), EDirection::EAST);
    TS_ASSERT_EQUALS(c2.nextDirection(), EDirection::NONE);
}

}
