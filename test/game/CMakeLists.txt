set(game_srcs
    CControllerTest.cpp
)

set(game_libs
    game
    mck_gamelib
    gamelib
    car
    map
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    game
    game_srcs
    game_libs
)
