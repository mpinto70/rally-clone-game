
add_library(
    minimap
    MiniMap.cpp
)

target_include_directories(
    minimap
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
