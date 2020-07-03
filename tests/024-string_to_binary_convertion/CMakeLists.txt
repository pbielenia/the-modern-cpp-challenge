cmake_minimum_required(VERSION 3.17)

include(GoogleTest)

set(target_name 024-string_to_binary_convertion_tests)
add_executable(${target_name} unit_tests.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name}
PRIVATE
	gtest
	gtest_main
	gmock
	024-string_to_binary_convertion
)

gtest_discover_tests(${target_name} TEST_PREFIX 24: )
