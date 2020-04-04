cmake_minimum_required(VERSION 3.14)
project(other C CXX)

add_executable(heap_and_stack heap_and_stack.cpp)
target_link_libraries(heap_and_stack pthread)

add_executable(auto_decltype auto_decltype.cpp)