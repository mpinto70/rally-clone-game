
add_library(
    car
    Car.cpp
    Direction.cpp
    Orientation.cpp
)

target_include_directories(
    car
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
