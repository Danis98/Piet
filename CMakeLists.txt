cmake_minimum_required(VERSION 3.20)
project(Piet)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/Users/danie/lib/install/libpng/include)
include_directories(C:/Users/danie/lib/install/zlib/include)
link_libraries(C:/Users/danie/lib/install/libpng/lib/libpng.a)
link_libraries(C:/Users/danie/lib/install/zlib/lib/zlib.lib)

add_executable(Piet main.cpp lib/codel.h lib/color.h lib/image.h lib/image_read.cpp lib/state.h lib/codel.cpp lib/color.cpp)
add_executable(Test tests/test_color.cpp lib/color.h tests/test_main.cpp tests/tests.h lib/state.h lib/codel.cpp lib/color.cpp)
target_include_directories(Piet PRIVATE lib)
target_include_directories(Test PRIVATE lib)
