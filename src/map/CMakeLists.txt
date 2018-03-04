
add_library(
    map
    Map.cpp
    MapIO.cpp
    Tile.cpp
    Action.cpp
    TileType.cpp
)

target_include_directories(
    map
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
