cmake_minimum_required(VERSION 3.17)
project(dlinkedlist C)

set(CMAKE_C_STANDARD 11)

add_executable(dlinkedlist main.c
        functions/insert_node.c
        headers/list.h util/error.c
        headers/types.h
        functions/util.c
        functions/delete_node.c functions/get_node.c util/error.h)