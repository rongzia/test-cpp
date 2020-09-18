protobuf_generate_cpp(PROTO_SRC PROTO_HEADER helloworld.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(helloworld_client client.cpp ${PROTO_SRC} ${PROTO_HEADER} ../flags_def.cpp)
add_executable(helloworld_server server.cpp ${PROTO_SRC} ${PROTO_HEADER} ../flags_def.cpp)

target_link_libraries(helloworld_client ${BRPC_LIB} ${DYNAMIC_LIB})
target_link_libraries(helloworld_server ${BRPC_LIB} ${DYNAMIC_LIB})