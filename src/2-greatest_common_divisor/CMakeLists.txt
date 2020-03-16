cmake_minimum_required(VERSION 3.17)
set(target_name 2-greatest_common_divisor)

add_executable(${target_name} solution.hpp tests.cpp)
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
