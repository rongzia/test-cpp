project(test-spdlog C CXX)
message(STATUS "PROJECT_NAME : " ${PROJECT_NAME})

include_directories(include)
add_executable(test src/test.cpp)
target_link_libraries(test pthread)