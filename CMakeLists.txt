cmake_minimum_required(VERSION 3.14)
project(test C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_subdirectory(test-libevent)
#add_subdirectory(test-grpc)
add_subdirectory(test-sizeOfStruct)
