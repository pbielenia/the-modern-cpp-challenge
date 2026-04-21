set(target_name 073-data_serialization_to_file)

find_package(pugixml REQUIRED)

add_executable(${target_name} solution.cpp tests.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_20)
target_link_libraries(${target_name}
    PRIVATE
        gtest::gtest
        pugixml::pugixml
)

target_compile_options(${target_name} 
   INTERFACE
        -Wall -Wextra -pedantic -Werror
)

file(COPY movies-list.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(GoogleTest)
gtest_discover_tests(${target_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_definitions(${target_name} PRIVATE
    RESOURCE_DIR="${CMAKE_CURRENT_BINARY_DIR}"
)
