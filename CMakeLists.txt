cmake_minimum_required(VERSION 3.20)
project(Piet)

set(CMAKE_CXX_STANDARD 20)

add_executable(Piet main.cpp lib/codel.h lib/color.h)
add_executable(Test tests/test_color.cpp lib/color.h tests/test_main.cpp tests/tests.h)
target_include_directories(Piet PRIVATE lib)
target_include_directories(Test PRIVATE lib)
