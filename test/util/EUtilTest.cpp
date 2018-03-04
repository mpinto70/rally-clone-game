#include "util/EUtil.h"

#include <gtest/gtest.h>

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

TEST(EUtilTest, Iteration) {
    const std::vector<Enum> enums = { Enum::ZERO, Enum::ONE, Enum::TWO, Enum::THREE };
    size_t i = 0;
    for (auto e : CEnumIterator<Enum>()) {
        EXPECT_EQ(e, enums[i]);
        ++i;
    }

    EXPECT_EQ(i, enums.size());
}

static void verifyConversion(unsigned value,
      Enum enum_value) {
    EXPECT_EQ(to_Enum<Enum>(value), enum_value);
    EXPECT_EQ(from_Enum<unsigned>(enum_value), value);
}

TEST(EUtilTest, Conversion) {
    verifyConversion(0, Enum::ZERO);
    verifyConversion(1, Enum::ONE);
    verifyConversion(2, Enum::TWO);
    verifyConversion(3, Enum::THREE);
}
}
