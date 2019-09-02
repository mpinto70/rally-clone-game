
add_library(
    gamelib_allegro_bmp
    BitmapReader.cpp
    SpriteReader.cpp
    CarMapper.cpp
        CarMapper.cpp)

target_include_directories(
    gamelib_allegro_bmp
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
