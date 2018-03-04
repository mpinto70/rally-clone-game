
add_library(
    tools_util
    helpers.cpp
)

target_include_directories(
    tools_util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
