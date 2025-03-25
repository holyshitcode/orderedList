cmake_minimum_required(VERSION 3.29)
project(orderedList C)

set(CMAKE_C_STANDARD 99)

add_executable(orderedList main.c
        unitTest.c)
