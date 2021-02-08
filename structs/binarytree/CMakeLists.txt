cmake_minimum_required(VERSION 3.17)
project(binarytree C)

set(CMAKE_C_STANDARD 11)

add_executable(binarytree main.c headers/types.h headers/binarytree.h util/error.c util/error.h util/util.c functions/traversal.c functions/minmax.c functions/successor.c functions/predecessor.c functions/delete.c functions/insert.c functions/search.c)