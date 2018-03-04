
add_library(
    gamelib_allegro
    GameLib.cpp
    Graphic.cpp
    Keyboard.cpp
    Sound.cpp
    Timer.cpp
)

target_include_directories(
    gamelib_allegro
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory (bmp)
