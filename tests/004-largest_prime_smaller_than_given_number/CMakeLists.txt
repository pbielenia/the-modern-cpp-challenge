cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 004-largest_prime_smaller_than_given_number_tests)
add_executable(${target_name} largest_prime_smaller_than_given_number.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    004-largest_prime_smaller_than_given_number
)

gtest_discover_tests(${target_name} TEST_PREFIX 4:)
