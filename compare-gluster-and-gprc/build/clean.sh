#!/usr/bin/env bash

rm -rf ../build/CMakeFiles
rm -rf ../build/gluster
rm -rf ../build/grpc
rm -rf ../build/util
rm ../build/cmake_install.cmake
rm ../build/CMakeCache.txt
rm LOG*
rm testfile
sudo rm ~/share-storage/mnt/testfile
rm grpc/testfile

