cmake_minimum_required(VERSION 3.9)
project(circular_buffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(circular_buffer
        main.cpp)
#        gtest.cpp
#        gtest/gtest-all.cc
#        gtest/gtest.h
#        gtest/gtest_main.cc counted.cpp)
target_link_libraries(circular_buffer -lpthread)