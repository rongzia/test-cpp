cmake_minimum_required(VERSION 3.14)
project(test-rdma C CXX)

add_executable(client client.cpp)
target_link_libraries(client pthread rdmacm ibverbs infinity)