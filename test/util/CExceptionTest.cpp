#include "util/CException.h"

#include <gtest/gtest.h>

#include <type_traits>

namespace util {

TEST(CExceptionTest, Hierarchy) {
    EXPECT_TRUE((std::is_base_of<std::runtime_error, CException>::value));
    EXPECT_TRUE((std::is_default_constructible<CException>::value) == false);
}

TEST(CExceptionTest, Creation) {
    CException e("message", 1);
    EXPECT_EQ(std::string(e.what()), "message");
    EXPECT_EQ(e.code(), 1);
}
}
