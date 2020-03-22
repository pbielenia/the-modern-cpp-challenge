cmake_minimum_required(VERSION 3.17)
set(target_name 17-creating_a_2d_array_with_basic_operations)

add_executable(${target_name} Array2D.hpp Array2D.cpp tests.cpp)
target_link_libraries(${target_name}
    PRIVATE
        gtest
        gmock
)

target_compile_options(${target_name} 
    PRIVATE
        -Wall -Wextra -pedantic -Werror
)

add_test(unit_tests unit_tests)

add_custom_command(
     TARGET ${target_name}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target_name}
)
