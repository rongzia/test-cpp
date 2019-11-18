cmake_minimum_required(VERSION 3.14)
project(test_boost)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "$ENV{HOME}")
message(STATUS "BOOST_ROOT : " "$ENV{BOOST_ROOT}")

find_package(Boost COMPONENTS thread)
message(STATUS "Boost_INCLUDE_DIRS : " ${Boost_INCLUDE_DIRS})
message(STATUS "Boost_LIBRARIES : " ${${Boost_LIBRARIES}})

message(STATUS "BOOST_LIBRARYDIR : " "$ENV{BOOST_LIBRARYDIR}")


include_directories(${Boost_INCLUDE_DIRS})

add_executable(test_boost main.cpp)

target_link_libraries(test_boost  Boost::thread)