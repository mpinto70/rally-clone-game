
add_library(
    gamelib_allegro_bmp
    SpriteReader.cpp
    CarMapper.cpp
    FuelMapper.cpp
    TileMapper.cpp
    MiniMapMapper.cpp
    ActionMapper.cpp
)

target_include_directories(
    gamelib_allegro_bmp
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
