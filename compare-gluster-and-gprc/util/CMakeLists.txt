#file(GLOB NAME_SRC *.h *.cpp)
set(NAME_SRC
        exception.h exception.cpp
        file_system.h file_system.cpp
        profiler.h
        string_util.h
        string_util.cpp
        )
add_executable(test_file
        test_file.cpp

        exception.cpp
        file_system.cpp
        string_util.cpp
        )

add_executable(test_time
        test_profiler.cpp

        profiler.h
)

# 在 lib 下生成动态库
add_library(
        test
#        SHARED
        ${NAME_SRC}
)
# 动态库输出到 lib 目录下
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)