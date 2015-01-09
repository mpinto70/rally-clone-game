
#pragma once

#include <cxxtest/TestSuite.h>

namespace util {

class TestCWait: public CxxTest::TestSuite {
    public:
        void testWait();
        void testEnd();
};

}
using util::TestCWait;

