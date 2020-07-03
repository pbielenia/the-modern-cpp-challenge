cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 015-ipv4_data_type_tests)
add_executable(${target_name} ipv4_data_type.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
    gtest
    gtest_main
    gmock
    015-ipv4_data_type
)

gtest_discover_tests(${target_name} TEST_PREFIX 15:)
