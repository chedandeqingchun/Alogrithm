cmake_minimum_required(VERSION 3.5.1)
project(algo C CXX)

set(CMAKE_C_COMPILER "g++")

set(source_files_sort
    sort.cpp
)

add_executable(sort ${source_files_sort})
add_subdirectory(useful_components)
