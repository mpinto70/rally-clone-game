
add_library(
    mck_game
    GameLibMock.cpp
    GameLibUtils.cpp
    GraphicMock.cpp
    KeyboardMock.cpp
    SoundMock.cpp
    TimerMock.cpp
)

target_include_directories(
    mck_game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
