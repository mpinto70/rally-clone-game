
#pragma once

#include <cxxtest/TestSuite.h>

namespace map {

class TestCMap: public CxxTest::TestSuite {
    public:
        void testCreation();
        void testInvalidCreation();
};

}
using map::TestCMap;

