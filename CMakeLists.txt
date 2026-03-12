cmake_minimum_required(VERSION 3.17)
project(modern_cpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(src)
