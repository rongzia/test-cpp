message("\n[${PROTO_NAME}.cmake] start")

add_custom_command(
        OUTPUT "${PROTO_DIR_AND_NAME}.pb.cc" "${PROTO_DIR_AND_NAME}.pb.h" "${PROTO_DIR_AND_NAME}.grpc.pb.cc" "${PROTO_DIR_AND_NAME}.grpc.pb.h"
        COMMAND ${PROTOBUF_DIR}/bin/protoc
        ARGS
        --grpc_out "${PROTO_DIR}"
        --cpp_out "${PROTO_DIR}"
        -I "${PROTO_DIR}"
        --plugin=protoc-gen-grpc=${GRPC_DIR}/bin/grpc_cpp_plugin
        "${PROTO_DIR_AND_NAME}.proto"
        DEPENDS "${PROTO_DIR_AND_NAME}.proto"
)

message("[${PROTO_NAME}.cmake] end\n")