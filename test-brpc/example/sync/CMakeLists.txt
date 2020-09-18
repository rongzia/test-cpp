protobuf_generate_cpp(PROTO_SRC PROTO_HEADER api.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_client test_client.cpp client_handler.cpp gflags_def.cpp ${PROTO_SRC} ${PROTO_HEADER})
add_executable(test_server test_server.cpp server_handler.cpp lock_service.cpp gflags_def.cpp ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(test_client ${BRPC_LIB} ${DYNAMIC_LIB})
target_link_libraries(test_server ${BRPC_LIB} ${DYNAMIC_LIB})
