cmake_minimum_required(VERSION 3.17)
set(target_name 2-greatest_common_divisor)
add_executable(${target_name} main.cpp)

target_compile_options(${target_name} 
    PRIVATE
        -Wall -Wextra -pedantic -Werror
)
