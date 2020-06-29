cmake_minimum_required(VERSION 3.17)

set(target_name 023-binary_to_string_conversion)

add_library(${target_name} STATIC src/BinToStrConverter.cpp)
target_include_directories(${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/binary_to_string_conversion>
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)
