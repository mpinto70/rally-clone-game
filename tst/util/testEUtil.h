
#pragma once

#include <cxxtest/TestSuite.h>

namespace util {

class TestEUtil: public CxxTest::TestSuite {
    public:
        void testIteration();
};

}
using util::TestEUtil;
