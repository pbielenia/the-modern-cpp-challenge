cmake_minimum_required(VERSION 3.17)

set(target_name 023-binary_to_string_conversion)

add_library(${target_name} INTERFACE)
target_include_directories(${target_name}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
