cmake_minimum_required(VERSION 3.17)
project(infinityCalculator C)

set(CMAKE_C_STANDARD 99)

add_executable(infinityCalculator
        main.c
        calculator.h
        calculator.c)