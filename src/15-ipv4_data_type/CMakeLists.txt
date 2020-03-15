cmake_minimum_required(VERSION 3.17)
set(target_name 15-ipv4_data_type)
add_executable(${target_name} main.cpp)

target_compile_options(${target_name} 
    PRIVATE
        -Wall -Wextra -pedantic -Werror
)
