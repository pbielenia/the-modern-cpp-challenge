cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(sources
    4-largest_prime_smaller_than_given_number.cpp
)

set(target_name 4-largest_prime_smaller_than_given_number_tests)
add_executable(${target_name} ${sources})
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    4-largest_prime_smaller_than_given_number
)

gtest_discover_tests(${target_name} TEST_PREFIX 4:)
