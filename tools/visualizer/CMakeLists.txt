
add_executable(
    visualizer
    visualizer.cpp
)

target_link_libraries(
    visualizer
    tools_util
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
