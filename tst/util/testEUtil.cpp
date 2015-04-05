
#include "testEUtil.h"

#include "util/EUtil.h"

#include <sys/time.h>
#include <vector>

namespace util {

enum class Enum : unsigned {
    ZERO,
    ONE,
    TWO,
    THREE,
    LAST,
    FIRST = ZERO
};

void TestEUtil::testIteration() {
    const std::vector<Enum> enums = { Enum::ZERO, Enum::ONE, Enum::TWO, Enum::THREE };
    size_t i = 0;
    for (auto e : CEnumIterator<Enum>()) {
        TS_ASSERT_EQUALS(e, enums[i]);
        ++i;
    }

    TS_ASSERT_EQUALS(i, enums.size());
}

static void verifyConversion(unsigned value,
                             Enum enum_value) {
    TS_ASSERT_EQUALS(to_Enum<Enum>(value), enum_value);
    TS_ASSERT_EQUALS(from_Enum<unsigned>(enum_value), value);
}

void TestEUtil::testConversion() {
    verifyConversion(0, Enum::ZERO);
    verifyConversion(1, Enum::ONE);
    verifyConversion(2, Enum::TWO);
    verifyConversion(3, Enum::THREE);
}

}

