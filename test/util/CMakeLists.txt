set(util_srcs
    ExceptionTest.cpp
    SingletonTest.cpp
    WaitTest.cpp
    UtilTest.cpp
)

set(util_libs
    util
)

add_unit_test(
    util
    util_srcs
    util_libs
)
