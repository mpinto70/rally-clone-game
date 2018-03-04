set(map_srcs
    CMapIOTest.cpp
    CMapTest.cpp
    CTileTest.cpp
    EActionTest.cpp
    ETileTypeTest.cpp
)

set(map_libs
    map
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    map
    map_srcs
    map_libs
)
