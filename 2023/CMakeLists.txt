cmake_minimum_required(VERSION 3.16)
project(aoc_2023)

add_compile_options(-ggdb -O0)

add_executable(day1 day1/day1.cpp)
add_executable(day1p2 day1/day1p2.cpp)
set_property(TARGET day1p2 PROPERTY CXX_STANDARD 20)

add_executable(day2 day2/day2.cpp)

add_executable(day3 day3/day3.cpp)

add_executable(day4 day4/day4.cpp)
set_property(TARGET day4 PROPERTY CXX_STANDARD 20)
