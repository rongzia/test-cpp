protobuf_generate_cpp(PROTO_SRC PROTO_HEADER test.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(tcp_client client.cpp ${PROTO_SRC} ${PROTO_HEADER})
add_executable(tcp_server server.cpp ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(tcp_client ${BRPC_LIB} ${DYNAMIC_LIB})
target_link_libraries(tcp_server ${BRPC_LIB} ${DYNAMIC_LIB})
