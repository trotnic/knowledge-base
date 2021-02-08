cmake_minimum_required(VERSION 3.17)
project(slinkedlist C)

set(CMAKE_C_STANDARD 11)

add_executable(slinkedlist main.c headers/list.h)