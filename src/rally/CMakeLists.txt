
add_executable(
    rally
    rally.cpp
)

target_link_libraries(
    rally
    gamelib_allegro
    gamelib_allegro_bmp
    game
    car
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
