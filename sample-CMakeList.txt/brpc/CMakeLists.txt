cmake_minimum_required(VERSION 3.14)
project(some C CXX)

# cmake 普遍采用 find_package 的方式寻找库，其实也就是在 cmake 安装目录有一些模板去寻找库，这些模板在 cmake-3.14.5/share/cmake-3.14/Modules，但是没有寻找 brpc 库的模板



# 寻找库
include(cmake/brpc.cmake)

# 设置生成代码名称，生成的代码放在 build 目录下
set(global_lock_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/global_lock_service.pb.cc")
set(global_lock_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/global_lock_service.pb.h")


### 最保险的做法，该命令会立即被调用。
execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        -I ${CMAKE_SOURCE_DIR}/proto                        # .proto 目录
        --cpp_out=${CMAKE_CURRENT_BINARY_DIR}               # 代码生成目录
        ${CMAKE_SOURCE_DIR}/protoc/some.proto)              # .proto 文件

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(some SHARED main.cpp)
target_link_libraries(some ${BRPC_LIB} ${DYNAMIC_LIB})
