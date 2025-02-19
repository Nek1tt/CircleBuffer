cmake_minimum_required(VERSION 3.10)
project(CircleBufferLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_STANDARD MATCHES "17")
    message(FATAL_ERROR "C++17 is required but not supported!")
endif()

add_library(CircleBuffer STATIC source/CircleBuffer.cpp)
target_include_directories(CircleBuffer PUBLIC headers)