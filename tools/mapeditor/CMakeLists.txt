
add_executable(
    map_editor
    map_editor.cpp
)

target_link_libraries(
    map_editor
    tools_util
    gamelib_allegro
    gamelib_allegro_bmp
    game
    car
    minimap
    map
    util
    allegro
    allegro_font
    allegro_ttf
    allegro_primitives
    allegro_image
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)
