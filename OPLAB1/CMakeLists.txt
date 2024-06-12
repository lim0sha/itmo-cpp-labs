cmake_minimum_required(VERSION 3.26)
project(OPLAB1
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labwork1"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

add_executable(OPLAB1
        "functions.cpp"
        "functions.h")
