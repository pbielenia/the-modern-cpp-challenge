cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 023-binary_to_string_conversion_tests)
add_executable(${target_name} binary_to_string_conversion.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    023-binary_to_string_conversion
)

gtest_discover_tests(${target_name} TEST_PREFIX 23:)
