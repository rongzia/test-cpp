cmake_minimum_required(VERSION 3.14)
project(test-cpp C CXX)
message(STATUS "PROJECT_NAME : " ${PROJECT_NAME})


#add_subdirectory(test-boost)
#add_subdirectory(compare-gluster-and-gprc)
add_subdirectory(util)
add_subdirectory(test-grpc2)