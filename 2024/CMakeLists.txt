cmake_minimum_required(VERSION 3.16)
project(aoc_2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb -O0)

find_package(fmt REQUIRED)

link_libraries(fmt::fmt)

add_executable(day1 day1/day1p1.cpp)

add_executable(day2 day2/day2.cpp)

add_executable(day3 day3/day3.cpp)

add_executable(day4 day4/day4.cpp)

add_executable(day5 day5/day5.cpp)

add_executable(day6 day6/day6.cpp)
