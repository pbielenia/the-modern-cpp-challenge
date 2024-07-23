cmake_minimum_required(VERSION 3.17)

set(target_name 015-ipv4_address)

add_library(${target_name} STATIC src/ipv4_address.cpp)

target_include_directories(${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ipv4_address>
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)
