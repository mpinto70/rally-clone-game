################################################################################
# Google Test Setup - BEGIN ####################################################
################################################################################

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(
    libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(
    libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

################################################################################
# Google Test Setup - END ######################################################
################################################################################

function(add_unit_test testname sources_var libs_var)
    add_executable(
        unit_${testname}
        ${PROJECT_SOURCE_DIR}/test/gtest_main.cpp
        ${${sources_var}}
    )

    include_directories(
        "${PROJECT_SOURCE_DIR}/gtest/src/gtest/googletest/include"
        "${PROJECT_SOURCE_DIR}/gtest/src/gtest/googlemock/include"
    )

    set_target_properties(
        unit_${testname}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/test/bin
    )

    target_link_libraries(
        unit_${testname}
        ${${libs_var}}
        libgtest
        libgmock
    )

    add_test(NAME unit_${testname} COMMAND ${PROJECT_SOURCE_DIR}/test/bin/unit_${testname})
endfunction(add_unit_test)
