cmake_minimum_required(VERSION 3.17)
set(target_name 1-sum_of_naturals_divisible_by_3_and_5)
add_executable(${target_name} main.cpp)

target_compile_options(${target_name} 
    PRIVATE
        -Wall -Wextra -pedantic -Werror
)
