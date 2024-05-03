cmake_minimum_required(VERSION 3.20)
project(chess)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++17 -g -Wall -Wextra -O2)

add_subdirectory(src)
add_subdirectory(test)