cmake_minimum_required (VERSION 3.12)

project("AOC2022")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(utils)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
