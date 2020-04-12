cmake_minimum_required(VERSION 3.14)
project(other C CXX)

add_executable(heap_and_stack heap_and_stack.cpp)
target_link_libraries(heap_and_stack pthread)

add_executable(auto_decltype auto_decltype.cpp)

add_executable(thread_join thread_join.cpp)
target_link_libraries(thread_join pthread)

add_executable(test_fstream test_fstream.cpp)