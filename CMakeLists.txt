cmake_minimum_required(VERSION 3.10)
project(kilo C)

set(CMAKE_C_STANDARD 11)

add_executable(kilo kilo.c
    data.h
    terminal/terminal.c
    terminal/terminal.h
    defines.h
    io/input.c
    io/input.h
    io/output.c
    io/output.h
    init.c
    init.h
    types/string_buf.c
    types/string_buf.h)
