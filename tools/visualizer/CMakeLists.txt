
add_executable(
    visualizer
    visualizer.cpp
)

target_link_libraries(
    visualizer
    tools_util
    gamelib_allegro
    gamelib_allegro_bmp
    game
    car
    map
    util
    alleg
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)
