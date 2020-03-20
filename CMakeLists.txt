cmake_minimum_required(VERSION 3.17)
project(modern_cpp)

include(cmake/SubmodulesUpdate.cmake)
update_submodules()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE debug)

add_subdirectory(libs/googletest)
add_subdirectory(src)
