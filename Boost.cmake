find_package(Boost 1.60.0 REQUIRED COMPONENTS system filesystem)

include_directories(
    ${Boost_INCLUDE_DIR}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
)
