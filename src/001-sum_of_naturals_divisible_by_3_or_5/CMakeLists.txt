cmake_minimum_required(VERSION 3.17)

set(target_name 001-sum_of_naturals_divisible_by_3_or_5)

add_executable(${target_name} tests.cpp solution.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
    PRIVATE
        gtest
        gtest_main
        gmock
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)

include(GoogleTest)
gtest_discover_tests(${target_name})
