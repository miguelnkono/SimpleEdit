cmake_minimum_required(VERSION 4.0)
project(kilo C)

set(CMAKE_C_STANDARD 11)

add_executable(kilo kilo.c
    data.h
    terminal/terminal.c
    terminal/terminal.h)
