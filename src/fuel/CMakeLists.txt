
add_library(
    fuel
    Fuel.cpp
)

target_include_directories(
    fuel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
