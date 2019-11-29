//
// Created by rrzhang on 2019/11/20.
//

#include <spdlog/spdlog.h>
#include "easylogger.h"
void fun1(){
    EasyLoggerWithTrace("./async_log.txt",EasyLogger::warn) << "fun1";
}
void fun2(){
    fun1();
    EasyLoggerWithTrace("./async_log.txt",EasyLogger::warn) << "fun2";
}
int main(void)
{
    EasyLogger easyLogger("test_log","./async_log.txt",EasyLogger::warn);

    EasyLoggerWithTrace("./async_log.txt",EasyLogger::warn) << "test log message";
    EasyLoggerWithTrace("./async_log.txt",EasyLogger::error) << "test log message";
    fun2();
    return 0;
}