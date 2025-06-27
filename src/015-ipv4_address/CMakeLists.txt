set(target_name 015-ipv4_address)

add_executable(${target_name} tests.cpp ipv4_address.cpp)
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
