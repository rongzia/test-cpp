cmake_minimum_required(VERSION 3.9)
project(test-grpc CXX)

set(PROTOC_DIR "protobuf-3.7.0")
set(PROTOC_NAME "test_grpc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib -L$ENV{HOME}/.local/grpc/lib -L$ENV{HOME}/.local/${PROTOC_DIR}/lib -lprotobuf -lgrpc++ -lgrpc -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl")

#add_definitions(-D TEST)

# protocbuf & grpc++ lib
find_library(_PROTOBUF_LIBPROTOBUF protobuf $ENV{HOME}/.local/${PROTOC_DIR}/lib)  # _PROTOBUF_LIBPROTOBUF: /home/rrzhang/.local/${PROTOC_DIR}/lib/libprotobuf.so
find_library(_GRPC_GRPCPP_UNSECURE grpc++_unsecure $ENV{HOME}/.local/grpc/lib)   # _GRPC_GRPCPP_UNSECURE: /home/rrzhang/.local/grpc/lib/libgrpc++_unsecure.so

include(${PROJECT_SOURCE_DIR}/cmake/${PROTOC_NAME}.cmake)

include_directories(
        $ENV{HOME}/.local/${PROTOC_DIR}/include
        $ENV{HOME}/.local/grpc/include
)
include_directories(include)
include_directories(src)
include_directories(protos)
include_directories(lib)


link_directories(lib/static)
add_executable(client
        ${PROJECT_SOURCE_DIR}/src/client/client.cpp
        ${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.grpc.pb.cc
        ${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.pb.cc
        )
target_link_libraries(client
        PerformanceOnetime
        ${_PROTOBUF_LIBPROTOBUF}
        ${_GRPC_GRPCPP_UNSECURE}
        dl
        pthread
        )
add_executable(server
        ${PROJECT_SOURCE_DIR}/src/server/server.cpp
        ${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.grpc.pb.cc
        ${PROJECT_SOURCE_DIR}/protos/${PROTOC_NAME}.pb.cc
        )
target_link_libraries(server
        PerformanceThread
        ${_PROTOBUF_LIBPROTOBUF}
        ${_GRPC_GRPCPP_UNSECURE}
        dl
        pthread
        )
#set(INC_DIR /home/rrzhang/WorkSpace/test-leveldb/include)
#set(LINK_DIR /home/rrzhang/WorkSpace/test-leveldb/lib)
#include_directories(${INC_DIR})
#link_libraries(/home/rrzhang/WorkSpace/test-leveldb/lib/libleveldb.a)
#add_executable(test-leveldb src/main.cpp)