cmake_minimum_required(VERSION 3.27)
project(CTetris C)

set(CMAKE_C_STANDARD 11)

add_executable(tetris main.c tetris.c tetris.h)
