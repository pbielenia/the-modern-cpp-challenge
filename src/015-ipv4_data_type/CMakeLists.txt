cmake_minimum_required(VERSION 3.17)

set(target_name 015-ipv4_data_type)

add_library(${target_name} STATIC src/IPv4Address.cpp)
target_include_directories(${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ipv4_data_type>
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)
