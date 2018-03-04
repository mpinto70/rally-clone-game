
add_library(
    mck_gamelib
    CGameLibMock.cpp
    CGameLibUtils.cpp
    CGraphicMock.cpp
    CKeyboardMock.cpp
    CSoundMock.cpp
    CTimerMock.cpp
)

target_include_directories(
    mck_gamelib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
