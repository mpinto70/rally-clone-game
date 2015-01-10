
#include "testCSingleton.h"

#include "util/CSingleton.h"

#include <type_traits>

namespace util {

void TestCSingleton::testHierarchy() {
    TS_ASSERT((std::is_constructible<CSingleton<int>>::value) == false);
}

void TestCSingleton::testCreation() {
    TS_ASSERT_THROWS_EQUALS(CSingleton<int>::instance(),
                            std::logic_error & e,
                            std::string(e.what()),
                            "CSingleton::instance - not created");
    TS_ASSERT_THROWS_EQUALS(CSingleton<int>::create<int>(nullptr),
                            std::logic_error & e,
                            std::string(e.what()),
                            "CSingleton::create - null pointer");

    TS_ASSERT_THROWS_NOTHING(CSingleton<int>::create(std::unique_ptr<int>(new int(120))));
    TS_ASSERT_THROWS_NOTHING(CSingleton<int>::instance());

    TS_ASSERT_EQUALS(CSingleton<int>::instance(), 120);
    CSingleton<int>::instance() = 121;
    TS_ASSERT_EQUALS(CSingleton<int>::instance(), 121);

    TS_ASSERT_THROWS_EQUALS(CSingleton<int>::create(std::unique_ptr<int>(new int(150))),
                            std::logic_error & e,
                            std::string(e.what()),
                            "CSingleton::create - already created");
    TS_ASSERT_EQUALS(&CSingleton<int>::instance(), &CSingleton<int>::instance());
}

}

