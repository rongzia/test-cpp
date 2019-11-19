
#find_package (glog
#        PATHS /home/rrzhang/.local/glog-0.4.0/lib/cmake/glog/glog-config.cmake
#        NO_DEFAULT_PATH
#        )
#
#find_package (glog
#        PATHS /home/rrzhang/.local/glog-0.4.0/lib/cmake/glog/glog-config.cmake
#        )
#find_package(gflags
#    PATHS /home/rrzhang/.local/gflags-2.2.0/lib/cmake/gflags/gflags-config.cmake
#        NO_DEFAULT_PATH
#)
#find_package(gflags
#        PATHS /home/rrzhang/.local/gflags-2.2.0/lib/cmake/gflags/gflags-config.cmake
#        )
INCLUDE_DIRECTORIES(/home/rrzhang/.local/glog-0.4.0/include)
INCLUDE_DIRECTORIES(/home/rrzhang/.local/gflags-2.2.0/include)

LINK_LIBRARIES(pthread)
LINK_LIBRARIES(/home/rrzhang/.local/glog-0.4.0/lib/libglog.a)
LINK_LIBRARIES(/home/rrzhang/.local/gflags-2.2.0/lib/libgflags.a)
add_executable(test_glog test_glog.cpp)


