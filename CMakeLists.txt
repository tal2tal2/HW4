cmake_minimum_required(VERSION 3.27)
project(HW4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW4
        grades.c
        grades.h
        liblinked-list.so
        linked-list.h)
