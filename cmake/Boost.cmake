find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIR}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
)
