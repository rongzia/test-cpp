cmake_minimum_required(VERSION 2.8)
project(sqlite_server C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib -L$ENV{HOME}/.local/grpc/lib -L$ENV{HOME}/.local/protobuf/lib -lprotobuf -lgrpc++ -lgrpc -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: " ${CMAKE_EXE_LINKER_FLAGS})

message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

# protocbuf & grpc++ lib
find_library(_PROTOBUF_LIBPROTOBUF protobuf $ENV{HOME}/.local/protobuf/lib)  # _PROTOBUF_LIBPROTOBUF: /home/rrzhang/.local/protobuf/lib/libprotobuf.so
find_library(_GRPC_GRPCPP_UNSECURE grpc++_unsecure $ENV{HOME}/.local/grpc/lib)   # _GRPC_GRPCPP_UNSECURE: /home/rrzhang/.local/grpc/lib/libgrpc++_unsecure.so


include(cmake/os_rpc.cmake)

include_directories(
        $ENV{HOME}/.local/protobuf/include
        $ENV{HOME}/.local/grpc/include
)

# Targets
foreach (_target
        server)
    add_executable(${_target}
            ${PROJECT_SOURCE_DIR}/src/${_target}.cpp
            ${${osrpc}_proto_srcs}
            ${${osrpc}_grpc_srcs}
            )
    target_link_libraries(${_target}
            ${PROJECT_SOURCE_DIR}/include/sqlite3.o
            ${_PROTOBUF_LIBPROTOBUF}
            ${_GRPC_GRPCPP_UNSECURE}
            #            ${_GRPC_LIBGRPC}
            dl
            pthread
            )
endforeach ()