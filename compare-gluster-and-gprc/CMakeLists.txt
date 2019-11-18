cmake_minimum_required(VERSION 3.9)
project(compare-gluster-and-gprc CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

include_directories(util)

add_subdirectory(util)
add_subdirectory(grpc)
add_subdirectory(gluster)