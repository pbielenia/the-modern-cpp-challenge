cmake_minimum_required(VERSION 3.17)
project(modern_cpp CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

option(ENABLE_TESTING "Enable tests builds" On)

if(ENABLE_TESTING)
    message(STATUS "Building with tests")
    enable_testing()
    add_subdirectory(tests)

    add_subdirectory(libs/googletest)
    # Disable installation of GTest
    set(INSTALL_GTEST OFF CACHE INTERNAL "")
endif()

add_subdirectory(src)
