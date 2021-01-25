cmake_minimum_required(VERSION 3.10)

project(blackjack)
add_executable(blackjack ${PROJECT_SOURCE_DIR}/blackjack.c)

add_library(Stack ${PROJECT_SOURCE_DIR}/../structs/stack_up_bottom.c)
target_link_libraries(blackjack PUBLIC Stack)