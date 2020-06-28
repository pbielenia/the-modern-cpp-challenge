cmake_minimum_required(VERSION 3.17)
project(modern_cpp CXX)

option(ENABLE_TESTING "Enable tests builds" On)
option(UPDATE_SUBMODULES "Enable updating git submodules" On)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

if(UPDATE_SUBMODULES)
    include(cmake/SubmodulesUpdate.cmake)
    update_submodules()
endif()

if(ENABLE_TESTING)
    message(STATUS "Building with tests")
    enable_testing()
    set(INSTALL_GTEST OFF CACHE INTERNAL "")
    add_subdirectory(libs/googletest)
    add_subdirectory(tests)
endif()

add_subdirectory(src)
