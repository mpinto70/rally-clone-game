
#pragma once

#include <cxxtest/TestSuite.h>

namespace util {

class TestCEnumIterator: public CxxTest::TestSuite {
    public:
        void testIteration();
};

}
using util::TestCEnumIterator;
