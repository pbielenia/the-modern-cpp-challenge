cmake_minimum_required(VERSION 3.17)

set(target_name 004-largest_prime_smaller_than_given_number)

add_library(${target_name} INTERFACE)
target_include_directories(${target_name}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)
