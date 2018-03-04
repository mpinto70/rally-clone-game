
add_library(
    gamelib
    IGameLib.cpp
    IGraphic.cpp
    IKeyboard.cpp
    ISound.cpp
    ITimer.cpp
)

target_include_directories(
    gamelib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory (allegro)
