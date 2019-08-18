cmake_minimum_required(VERSION 3.13)
project(APUE C)

set(CMAKE_C_STANDARD 11)

add_library(APUE library.c library.h)

add_executable(main main.c)
