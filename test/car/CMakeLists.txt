set(car_srcs
    CarTest.cpp
    DirectionTest.cpp
    OrientationTest.cpp
)

set(car_libs
    car
    util
)

add_unit_test(
    car
    car_srcs
    car_libs
)
