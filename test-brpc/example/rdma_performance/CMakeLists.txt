protobuf_generate_cpp(PROTO_SRC PROTO_HEADER test.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(perf_client client.cpp ${PROTO_SRC} ${PROTO_HEADER})
add_executable(perf_server server.cpp ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(perf_client ${BRPC_LIB} ${DYNAMIC_LIB})
target_link_libraries(perf_server ${BRPC_LIB} ${DYNAMIC_LIB})
