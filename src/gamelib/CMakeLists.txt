
add_library(
    gamelib
    GameLib.cpp
    Graphic.cpp
    Keyboard.cpp
    Sound.cpp
    Timer.cpp
)

target_include_directories(
    gamelib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory (allegro)
