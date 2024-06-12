cmake_minimum_required(VERSION 3.26)
project(OPLAB5
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labwork5"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(OPLAB5 main.cpp template_func.cpp template_func.h template_stack.cpp template_stack.h)