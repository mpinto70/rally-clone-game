
add_library(
    game
    Controller.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
