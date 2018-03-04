#include "util/Exception.h"

#include <gtest/gtest.h>

#include <type_traits>

namespace util {

TEST(ExceptionTest, Hierarchy) {
    EXPECT_TRUE((std::is_base_of<std::runtime_error, Exception>::value));
    EXPECT_TRUE((std::is_default_constructible<Exception>::value) == false);
}

TEST(ExceptionTest, Creation) {
    Exception e("message", 1);
    EXPECT_EQ(std::string(e.what()), "message");
    EXPECT_EQ(e.code(), 1);
}
}
