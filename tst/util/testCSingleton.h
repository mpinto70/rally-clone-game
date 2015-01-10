
#pragma once

#include <cxxtest/TestSuite.h>

namespace util {

class TestCSingleton: public CxxTest::TestSuite {
    public:
        void testHierarchy();
        void testCreation();
};

}
using util::TestCSingleton;

