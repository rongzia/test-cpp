
add_executable(hello hello.cpp)

link_directories(/home/rrzhang/.local/libevent/lib)
add_executable(server server.cpp)
target_link_libraries(server event)

add_executable(client new-client.cpp)
target_link_libraries(client event)

