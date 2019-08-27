cmake_minimum_required(VERSION 3.13)
project(big_array_of_doubles_sorter)

set(CMAKE_CXX_STANDARD 14)

include_directories(libraries)

file( GLOB SRC_FILES
        *.cpp
        )

add_executable(big_array_of_doubles_sorter ${SRC_FILES})