cmake_minimum_required(VERSION 3.17)
project(modern_cpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

enable_testing()

add_subdirectory(libs/googletest)
add_subdirectory(src)

# Disable installation of GTest
set(INSTALL_GTEST OFF CACHE INTERNAL "")
