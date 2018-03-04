
add_executable(
    map_editor
    map_editor.cpp
)

target_link_libraries(
    map_editor
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
