cmake_minimum_required(VERSION 3.27)
project(OPLAB9
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labwork9"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

if (WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

include(FetchContent)
FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_7_1
)
FetchContent_MakeAvailable(curl)

add_executable(OPLAB9 main.cpp request_class.h parser_class.h currency_class.h curl_request.h)
target_link_libraries(OPLAB9 PUBLIC libcurl)

