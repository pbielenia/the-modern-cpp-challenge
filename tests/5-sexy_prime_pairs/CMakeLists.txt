cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(sources
    5-sexy_prime_pairs.cpp
)

set(target_name 5-sexy_prime_pairs_tests)
add_executable(${target_name} ${sources})
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    5-sexy_prime_pairs
)

gtest_discover_tests(${target_name} TEST_PREFIX 5:)
