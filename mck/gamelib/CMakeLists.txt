
add_library(
    mck_gamelib
    GameLibMock.cpp
    GameLibUtils.cpp
    GraphicMock.cpp
    KeyboardMock.cpp
    SoundMock.cpp
    TimerMock.cpp
)

target_include_directories(
    mck_gamelib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
