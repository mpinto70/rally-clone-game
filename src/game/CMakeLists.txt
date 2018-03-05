
add_library(
    game
    Controller.cpp
    GameLib.cpp
    Graphic.cpp
    Keyboard.cpp
    Sound.cpp
    Timer.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
