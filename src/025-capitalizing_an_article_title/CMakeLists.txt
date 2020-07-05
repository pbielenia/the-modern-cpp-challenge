cmake_minimum_required(VERSION 3.17)

set(target_name 025-capitalizing_an_article_title)

add_library(${target_name} STATIC src/TitleCapitalizer.cpp)
target_include_directories(${target_name}
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/capitalizing_an_article_title>
)

target_compile_options(${target_name}
PRIVATE
	-Wall -Wextra -pedantic -Werror
)
