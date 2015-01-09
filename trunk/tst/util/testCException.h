
#pragma once

#include <cxxtest/TestSuite.h>

namespace util {

class TestCException: public CxxTest::TestSuite {
    public:
        void testHierarchy();
        void testCreation();
};

}
using util::TestCException;

