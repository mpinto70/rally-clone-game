
#ifndef TESTCWAIT_RALLY
#define TESTCWAIT_RALLY

#include <cxxtest/TestSuite.h>

namespace util {
namespace tst {

class TestCWait: public CxxTest::TestSuite {
    public:
        void testWait();
        void testEnd();
};

}
}
using util::tst::TestCWait;

#endif

