
#include "testCEnumIterator.h"

#include "util/CEnumIterator.h"

#include <sys/time.h>
#include <vector>

namespace util {

enum class Enum : unsigned {
    ONE,
    TWO,
    THREE,
    LAST,
    FIRST = ONE
};

void TestCEnumIterator::testIteration() {
    const std::vector<Enum> enums = { Enum::ONE , Enum::TWO , Enum::THREE };
    size_t i = 0;
    for (auto e : CEnumIterator<Enum>()) {
        TS_ASSERT_EQUALS(e, enums[i]);
        ++i;
    }

    TS_ASSERT_EQUALS(i, enums.size());
}

}

