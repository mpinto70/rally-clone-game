
add_library(
    gamelib_allegro
    CGameLib.cpp
    CGraphic.cpp
    CKeyboard.cpp
    CSound.cpp
    CTimer.cpp
)

target_include_directories(
    gamelib_allegro
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
