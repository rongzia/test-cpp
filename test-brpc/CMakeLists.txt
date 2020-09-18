cmake_minimum_required(VERSION 3.14)
project(test_brpc C CXX)
set(CMAKE_CXX_STANDARD 11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(util)

include(cmake/brpc.cmake)

include_directories(include)

add_subdirectory(example/helloworld_sync)
add_subdirectory(example/helloworld_async)
add_subdirectory(example/sync)
add_subdirectory(example/tcp_performance)
add_subdirectory(example/rdma_performance)

