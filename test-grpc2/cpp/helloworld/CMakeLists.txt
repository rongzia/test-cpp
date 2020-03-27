cmake_minimum_required(VERSION 3.5.1)
project(HelloWorld C CXX)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
    add_definitions(-D_WIN32_WINNT=0x600)
endif ()

# libraries
set(PROTOBUF_ROOT $ENV{HOME}/.local/protobuf-3.6.1)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/protobuf.cmake)
set(GRPC_ROOT $ENV{HOME}/.local/grpc-v1.23.x)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/grpc.cmake)
message("find PROTOBUF_LIBRARY : " ${PROTOBUF_LIBRARY})
message("find PROTOBUF_PROTOC_EXECUTABLE : " ${PROTOBUF_PROTOC_EXECUTABLE})
message("find GRPC_STATIC_LIBRARY : " ${GRPC_STATIC_LIBRARY})
message("find GRPC_CPP_PLUGIN_EXECUTABLE : " ${GRPC_CPP_PLUGIN_EXECUTABLE})

find_library(ZLIB_LIBRARY libz.so /usr/lib/x86_64-linux-gnu/)

# Generated sources
set(PROTO_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../protos")
set(PROTO_GEN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto")
add_custom_command(
        OUTPUT "${PROTO_GEN_PATH}/helloworld.pb.cc" "${PROTO_GEN_PATH}/helloworld.pb.h"
        "${PROTO_GEN_PATH}/helloworld.grpc.pb.cc" "${PROTO_GEN_PATH}/helloworld.grpc.pb.h"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS --grpc_out "${PROTO_GEN_PATH}"
        --cpp_out "${PROTO_GEN_PATH}"
        -I "${PROTO_SOURCE_PATH}"
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${PROTO_SOURCE_PATH}/helloworld.proto"
        DEPENDS "${PROTO_SOURCE_PATH}/helloworld.proto")

# Include generated *.pb.h files
include_directories(proto)
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${GRPC_INCLUDE_DIR})

# Targets greeter_[async_](client|server)
foreach (_target
        greeter_client greeter_server
        greeter_async_client greeter_async_server)
    add_executable(${_target} "${_target}.cc"
            ${CMAKE_CURRENT_SOURCE_DIR}/proto/helloworld.pb.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/proto/helloworld.grpc.pb.cc)
    target_link_libraries(${_target}
            ${GRPC_STATIC_LIBRARY}
            ${PROTOBUF_LIBRARY}
            ${ZLIB_LIBRARY}
            pthread)
endforeach ()
