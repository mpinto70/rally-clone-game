#include "util/CSingleton.h"

#include <gtest/gtest.h>

#include <type_traits>

namespace util {

TEST(CSingletonTest, Hierarchy) {
    EXPECT_TRUE((std::is_constructible<CSingleton<int>>::value) == false);
}

TEST(CSingletonTest, Creation) {
    EXPECT_THROW(CSingleton<int>::instance(),
          std::logic_error);
    EXPECT_THROW(CSingleton<int>::create<int>(nullptr),
          std::logic_error);

    EXPECT_NO_THROW(CSingleton<int>::create(std::unique_ptr<int>(new int(120))));
    EXPECT_NO_THROW(CSingleton<int>::instance());

    EXPECT_EQ(CSingleton<int>::instance(), 120);
    CSingleton<int>::instance() = 121;
    EXPECT_EQ(CSingleton<int>::instance(), 121);

    EXPECT_THROW(CSingleton<int>::create(std::unique_ptr<int>(new int(150))),
          std::logic_error);
    EXPECT_EQ(&CSingleton<int>::instance(), &CSingleton<int>::instance());
}
}
