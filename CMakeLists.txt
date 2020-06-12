cmake_minimum_required(VERSION 3.15)
project(LearnIPC C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lpthread)

add_executable(LearnIPC main.c)