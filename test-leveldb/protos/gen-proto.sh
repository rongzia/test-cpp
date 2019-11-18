#!/bin/bash

cd ~/WorkSpace/test-leveldb/protos/
~/.local/protobuf-3.7.0/bin/protoc -I ./ --cpp_out=./ ./leveldb_cs.proto
~/.local/protobuf-3.7.0/bin/protoc -I ./ --grpc_out=./ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./leveldb_cs.proto