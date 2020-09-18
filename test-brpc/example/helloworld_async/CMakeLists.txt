protobuf_generate_cpp(PROTO_SRC PROTO_HEADER helloworld.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(client_helloworld_async client.cpp ${PROTO_SRC} ${PROTO_HEADER} ../flags_def.cpp)
add_executable(server_helloworld_async server.cpp ${PROTO_SRC} ${PROTO_HEADER} ../flags_def.cpp)

target_link_libraries(client_helloworld_async ${BRPC_LIB} ${DYNAMIC_LIB})
target_link_libraries(server_helloworld_async ${BRPC_LIB} ${DYNAMIC_LIB})