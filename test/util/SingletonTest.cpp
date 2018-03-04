#include "util/Singleton.h"

#include <gtest/gtest.h>

#include <type_traits>

namespace util {

TEST(SingletonTest, Hierarchy) {
    EXPECT_TRUE((std::is_constructible<Singleton<int>>::value) == false);
}

TEST(SingletonTest, Creation) {
    EXPECT_THROW(Singleton<int>::instance(),
          std::logic_error);
    EXPECT_THROW(Singleton<int>::create<int>(nullptr),
          std::logic_error);

    EXPECT_NO_THROW(Singleton<int>::create(std::unique_ptr<int>(new int(120))));
    EXPECT_NO_THROW(Singleton<int>::instance());

    EXPECT_EQ(Singleton<int>::instance(), 120);
    Singleton<int>::instance() = 121;
    EXPECT_EQ(Singleton<int>::instance(), 121);

    EXPECT_THROW(Singleton<int>::create(std::unique_ptr<int>(new int(150))),
          std::logic_error);
    EXPECT_EQ(&Singleton<int>::instance(), &Singleton<int>::instance());
}
}
