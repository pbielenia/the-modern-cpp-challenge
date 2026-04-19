set(target_name 067-password_validation)

add_executable(${target_name} solution.cpp tests.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_20)
target_link_libraries(${target_name}
    PRIVATE
        gtest::gtest
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)

include(GoogleTest)
gtest_discover_tests(${target_name})
