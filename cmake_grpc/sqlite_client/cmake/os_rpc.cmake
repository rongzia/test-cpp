


# protoc & grpc_cpp_plugin
find_file(_PROTOBUF_PROTOC protoc $ENV{HOME}/.local/protobuf/bin)
find_file(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin $ENV{HOME}/.local/grpc/bin)

set(osrpc "os_rpc")
# Proto file
get_filename_component(${osrpc}_proto "${PROJECT_SOURCE_DIR}/protos/${osrpc}.proto" ABSOLUTE)
get_filename_component(${osrpc}_proto_path "${${osrpc}_proto}" PATH)

set(${osrpc}_proto_srcs "${PROJECT_SOURCE_DIR}/pb/${osrpc}.pb.cc")
set(${osrpc}_proto_hdrs "${PROJECT_SOURCE_DIR}/pb/${osrpc}.pb.h")
set(${osrpc}_grpc_srcs "${PROJECT_SOURCE_DIR}/pb/${osrpc}.grpc.pb.cc")
set(${osrpc}_grpc_hdrs "${PROJECT_SOURCE_DIR}/pb/${osrpc}.grpc.pb.h")

add_custom_command(
        OUTPUT "${${osrpc}_proto_srcs}" "${${osrpc}_proto_hdrs}" "${${osrpc}_grpc_srcs}" "${${osrpc}_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${PROJECT_SOURCE_DIR}/pb"
        --cpp_out "${PROJECT_SOURCE_DIR}/pb"
        -I "${${osrpc}_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${${osrpc}_proto}"
        DEPENDS "${${osrpc}_proto}"
)