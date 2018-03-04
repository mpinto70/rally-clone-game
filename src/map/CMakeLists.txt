
add_library(
    map
    CMap.cpp
    CMapIO.cpp
    CTile.cpp
    EAction.cpp
    ETileType.cpp
)

target_include_directories(
    map
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
