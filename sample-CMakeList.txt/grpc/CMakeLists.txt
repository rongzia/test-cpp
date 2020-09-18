cmake_minimum_required(VERSION 3.14)
project(some C CXX)

# cmake 普遍采用 find_package 的方式寻找库，其实也就是在 cmake 安装目录有一些模板去寻找库，这些模板在 cmake-3.14.5/share/cmake-3.14/Modules，但是没有寻找 grpc 库的模板
# grpc 安装目录有个文件夹： grpc/lib64/cmake，是 grpc 自己写的 cmake 模板，但是特别难用，可能是新语法的缘故。。。



# 寻找库
set(Protobuf_ROOT $ENV{HOME}/.local/grpc)   # 高版本 grpc 编译时用的源码下的 protobuf，一并安装了 protobuf，使用库时要链接同样版本的 protobuf
set(gRPC_ROOT     $ENV{HOME}/.local/grpc)
# 动态库
include(${CMAKE_SOURCE_DIR}/cmake/protobuf-shared.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/grpc-shared.cmake)
# 静态库
include(${CMAKE_SOURCE_DIR}/cmake/protobuf-static.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/grpc-static.cmake)
find_library(ZLIB_LIBRARY libz.so /usr/lib/x86_64-linux-gnu/)
include_directories(${Protobuf_INCLUDE_DIR})
include_directories(${gRPC_INCLUDE_DIR})

# 设置生成代码名称，生成的代码放在 build 目录下
set(ds_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/some.pb.cc")
set(ds_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/some.pb.h")
set(ds_grpc_srcs  "${CMAKE_CURRENT_BINARY_DIR}/some.grpc.pb.cc")
set(ds_grpc_hdrs  "${CMAKE_CURRENT_BINARY_DIR}/some.grpc.pb.h")


### 最保险的做法，该命令会立即被调用。
execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        -I ${CMAKE_SOURCE_DIR}/proto                        # .proto 目录
        --cpp_out=${CMAKE_CURRENT_BINARY_DIR}               # 代码生成目录
        ${CMAKE_SOURCE_DIR}/protoc/some.proto)              # .proto 文件
execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        -I ${CMAKE_SOURCE_DIR}/proto                        # .proto 目录
        --grpc_out=${CMAKE_CURRENT_BINARY_DIR}              # 代码生成目录
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/protoc/some.proto)              # .proto 文件
# 包含 some.grpc.pb.h some.pb.h 的目录
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(some SHARED main.cpp)
# 动态库
target_link_libraries(some ${gRPC_GRPC++_REFLECTION_LIBRARY_SHARED} ${gRPC_GRPCPP_SHARED} ${Protobuf_LIBRARY_SHARED} ${ZLIB_LIBRARY})
# 静态库
target_link_libraries(some ${GRPC_STATIC_LIBRARY} ${Protobuf_LIBRARIES} ${ZLIB_LIBRARY})
