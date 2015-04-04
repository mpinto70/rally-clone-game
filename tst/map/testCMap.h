
#pragma once

#include <cxxtest/TestSuite.h>

namespace map {

class testCMap: public CxxTest::TestSuite {
    public:
        void testCreation();
        void testInvalidCreation();
};

}
using map::testCMap;

