
add_executable(
    rally
    rally.cpp
)

target_link_libraries(
    rally
    game
    gamelib_allegro
    gamelib_allegro_bmp
    gamelib
    car
    map
    util
    alleg
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)
