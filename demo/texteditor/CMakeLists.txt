cmake_minimum_required(VERSION 3.10)

project(uditor)
add_executable(uditor ${PROJECT_SOURCE_DIR}/program.c)

add_library(Stack ${PROJECT_SOURCE_DIR}/../../structs/stack_up_bottom.c)
target_link_libraries(uditor PUBLIC Stack)
