cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 001-sum_of_naturals_divisible_by_3_or_5-tests)
add_executable(${target_name} sum_of_naturals_divisible_by_3_or_5.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    001-sum_of_naturals_divisible_by_3_or_5
)

gtest_discover_tests(${target_name} TEST_PREFIX 1:)
