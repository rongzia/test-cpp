link_directories(lib)
add_executable(test_gluster
        test_gluster.cpp
        )
target_link_libraries(test_gluster
        test
        )