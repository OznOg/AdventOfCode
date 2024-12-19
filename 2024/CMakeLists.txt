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
target_compile_options(day6 PUBLIC -O3)

add_executable(day7 day7/day7.cpp)

add_executable(day8 day8/day8.cpp)

add_executable(day9 day9/day9.cpp)

add_executable(day10 day10/day10.cpp)

add_executable(day11 day11/day11.cpp)
target_compile_options(day11 PUBLIC -O3)

add_executable(day12 day12/day12.cpp)

add_executable(day13 day13/day13.cpp)
target_compile_options(day13 PUBLIC -O3)

add_executable(day14 day14/day14.cpp)

add_executable(day15 day15/day15.cpp)

add_executable(day16 day16/day16.cpp)

add_executable(day17 day17/day17.cpp)

add_executable(day18 day18/day18.cpp)

add_executable(day19 day19/day19.cpp)
