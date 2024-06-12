cmake_minimum_required(VERSION 3.26)
project(OPLAB2
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labwork2"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(include)
add_subdirectory(bin)

