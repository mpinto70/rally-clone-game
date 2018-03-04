
add_library(
    car
    CCar.cpp
    EDirection.cpp
    EOrientation.cpp
)

target_include_directories(
    car
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
