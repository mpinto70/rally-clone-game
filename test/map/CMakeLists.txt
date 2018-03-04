set(map_srcs
    MapIOTest.cpp
    MapTest.cpp
    TileTest.cpp
    ActionTest.cpp
    TileTypeTest.cpp
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
