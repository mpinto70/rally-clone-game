
#pragma once

#include <cxxtest/TestSuite.h>

namespace game {

class testCController: public CxxTest::TestSuite {
    public:
        void testCreation();
        void testInvalidCreation();
};

}
using game::testCController;

