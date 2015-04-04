
#pragma once

#include <cxxtest/TestSuite.h>

namespace map {

class testCMapIO: public CxxTest::TestSuite {
    public:
        void tearDown() override;
        void testRead();
        void testWrite();
};

}
using map::testCMapIO;

