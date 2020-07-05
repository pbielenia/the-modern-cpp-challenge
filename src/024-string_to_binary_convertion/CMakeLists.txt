cmake_minimum_required(VERSION 3.17)

set(target_name 024-string_to_binary_convertion)

add_library(${target_name} STATIC src/StrToBinConverter.cpp)
target_include_directories(${target_name}
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/string_to_binary_convertion>
)

target_compile_options(${target_name}
PRIVATE
	-Wall -Wextra -pedantic -Werror
)
