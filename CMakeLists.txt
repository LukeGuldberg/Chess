cmake_minimum_required(VERSION 3.20)
project(chess)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++17 -g -Wall -Wextra)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)

# project wide compilation settings
add_compile_options(-std=c++17 -ggdb -O3)

# divide project into src and testing folders
add_subdirectory(src)
add_subdirectory(test)
