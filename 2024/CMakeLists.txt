cmake_minimum_required(VERSION 3.16)
project(aoc_2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb -O0)

find_package(fmt REQUIRED)

link_libraries(fmt::fmt)

add_executable(day1 day1/day1p1.cpp)



