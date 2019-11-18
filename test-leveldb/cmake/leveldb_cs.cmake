#message("[leveldb_cs.cmake] start")

set(PROTOC_NAME "leveldb_cs")
set(PROTOS_DIR_AND_NAME "${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}")

add_custom_command(
        OUTPUT "${PROTOS_DIR_AND_NAME}.pb.cc" "${PROTOS_DIR_AND_NAME}.pb.h" "${PROTOS_DIR_AND_NAME}.grpc.pb.cc" "${PROTOS_DIR_AND_NAME}.grpc.pb.h"
        COMMAND $ENV{HOME}/.local/${PROTOC_DIR}/bin/protoc
        ARGS
        --grpc_out "${PROJECT_SOURCE_DIR}/protos"
        --cpp_out "${PROJECT_SOURCE_DIR}/protos"
        -I "${PROJECT_SOURCE_DIR}/protos"
        --plugin=protoc-gen-grpc=$ENV{HOME}/.local/grpc/bin/grpc_cpp_plugin
        "${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.proto"
        DEPENDS "${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.proto"
)

#message("[leveldb_cs.cmake] end")