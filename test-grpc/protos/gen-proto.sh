#!/bin/bash

cd ~/WorkSpace/test-grpc/protos/
~/.local/protobuf-3.7.0/bin/protoc -I ./ --cpp_out=./ ./test_grpc.proto
~/.local/protobuf-3.7.0/bin/protoc -I ./ --grpc_out=./ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./test_grpc.proto