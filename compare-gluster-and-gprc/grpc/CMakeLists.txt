
message(STATUS "PROJECT_SOURCE_DIR : " ${PROJECT_SOURCE_DIR})

set(PROTOBUF_DIR "$ENV{HOME}/.local/protobuf-3.7.0")    # protobuf 目录
set(GRPC_DIR "$ENV{HOME}/.local/grpc")                  # grpc 目录

set(PROTO_NAME "test")                                  # proto 名称
set(PROTO_DIR "${PROJECT_SOURCE_DIR}/grpc/protos")      # proto 生成的 .h .cc 目录
set(PROTO_DIR_AND_NAME "${PROTO_DIR}/${PROTO_NAME}")                  # proto目录/proto名称

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib -L${GRPC_DIR}/lib -L${PROTOBUF_DIR}/lib -lprotobuf -lgrpc++ -lgrpc -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl")


# protocbuf & grpc++ lib
find_library(_PROTOBUF_LIBPROTOBUF protobuf ${PROTOBUF_DIR}/lib)        # _PROTOBUF_LIBPROTOBUF: ${PROTOBUF_DIR}/lib/libprotobuf.so
find_library(_GRPC_GRPCPP_UNSECURE grpc++_unsecure ${GRPC_DIR}/lib)     # _GRPC_GRPCPP_UNSECURE: ${GRPC_DIR}/lib/libgrpc++_unsecure.so

include(test.cmake)
include_directories(
        ${PROTOBUF_DIR}/include     # protobuf 安装目录下 include
        ${GRPC_DIR}/include         # grpc 安装目录下 include

        ${PROTO_DIR}                # protos/*.h
        ${PROJECT_SOURCE_DIR}/util  # util
)

link_directories(lib)
foreach (_target server client)
    add_executable(${_target}
            ${_target}.cpp
            ${PROTO_DIR_AND_NAME}.grpc.pb.cc
            ${PROTO_DIR_AND_NAME}.pb.cc
            )
    target_link_libraries(${_target}
            test
            ${_PROTOBUF_LIBPROTOBUF}
            ${_GRPC_GRPCPP_UNSECURE}
            dl
            pthread
            )
endforeach ()
