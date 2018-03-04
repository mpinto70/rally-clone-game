
add_library(
    util
    Exception.cpp
    Wait.cpp
)

target_include_directories(
    util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
