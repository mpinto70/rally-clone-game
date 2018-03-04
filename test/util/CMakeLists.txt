set(util_srcs
    CExceptionTest.cpp
    CSingletonTest.cpp
    CWaitTest.cpp
    EUtilTest.cpp
)

set(util_libs
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    util
    util_srcs
    util_libs
)
