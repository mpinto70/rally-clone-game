
#pragma once

#include <cxxtest/TestSuite.h>

namespace map {

class testCTile: public CxxTest::TestSuite {
    public:
        void testCreation();
        void testModification();
};

}
using map::testCTile;

