cmake_minimum_required(VERSION 2.8)
project(project4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        variable.h
        variable.cpp
        function.h
        function.cpp
        graph.h
        graph.cpp)
add_executable(project4 ${SOURCE_FILES})