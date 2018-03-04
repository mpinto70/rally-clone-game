
add_library(
    util
    CException.cpp
    CWait.cpp
)

target_include_directories(
    util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
