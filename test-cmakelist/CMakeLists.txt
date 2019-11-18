cmake_minimum_required(VERSION 3.14)
project(test_cmakelist)

set(CMAKE_CXX_STANDARD 11)


set(MY_VAL "parent")
message("-- parent dir, MY_VAL : " ${MY_VAL})
add_subdirectory(subdir1)
message("-- parent dir, MY_VAL : " ${MY_VAL})
#add_subdirectory(subdir1/subdir2)

add_executable(test_cmakelist main.cpp)