cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 6-abundant_numbers_tests)
add_executable(${target_name} 6-abundant_numbers)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    6-abundant_numbers
)

gtest_discover_tests(${target_name} TEST_PREFIX 6:)
