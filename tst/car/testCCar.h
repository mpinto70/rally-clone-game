
#pragma once

#include <cxxtest/TestSuite.h>

namespace car {

class testCCar: public CxxTest::TestSuite {
    public:
        void testCreation();
        void testInvalidCreation();
        void testTurn();
};

}
using car::testCCar;

