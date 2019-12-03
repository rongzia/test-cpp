cmake_minimum_required(VERSION 3.14)
project(test-libevent CXX)



add_subdirectory(libevent)

include_directories(${PROJECT_SOURCE_DIR}/libevent/include)
include_directories(${PROJECT_SOURCE_DIR}/libevent/event2/include)

add_executable(server server.cpp)
target_link_libraries(server event)
target_link_libraries(server pthread)

add_executable(client client.cpp)
target_link_libraries(client event)
target_link_libraries(client pthread)


