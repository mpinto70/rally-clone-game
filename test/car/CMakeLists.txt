set(car_srcs
    CarTest.cpp
    DirectionTest.cpp
    OrientationTest.cpp
)

set(car_libs
    car
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    car
    car_srcs
    car_libs
)
