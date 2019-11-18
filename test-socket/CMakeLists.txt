cmake_minimum_required(VERSION 3.14)
project(test_socket)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-D TEST)

include_directories(include)


link_directories(lib/static)
add_executable(client src/client.cpp)
add_executable(server src/server.cpp)
target_link_libraries(client
        PerformanceOnetime
        )
target_link_libraries(server
        PerformanceOnetime
        pthread
        )
