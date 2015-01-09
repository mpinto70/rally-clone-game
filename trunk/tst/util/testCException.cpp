
#include "testCException.h"

#include "util/CException.h"

#include <type_traits>

namespace util {

void TestCException::testHierarchy() {
    TS_ASSERT((std::is_base_of<std::runtime_error, CException>::value));
    TS_ASSERT((std::is_default_constructible<CException>::value) == false);
}

void TestCException::testCreation() {
    CException e("message", 1);
    TS_ASSERT_EQUALS(std::string(e.what()), "message");
    TS_ASSERT_EQUALS(e.code(), 1);
}

}

