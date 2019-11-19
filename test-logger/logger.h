//
// Created by rrzhang on 2019/11/18.
//

#ifndef TEST_LOGGER_H
#define TEST_LOGGER_H

#include <ostream>
#include <fstream>
#include <iostream>

//#define DEBUG_FLAG

enum class LogRank {
    INFO,
    WARNING,
    ERROR,
    FATAL
};

enum class LogType {
    NORMAL,
    SIMPLE,
    FUNC
};

std::ostream &Log(LogType logType, const int line, const std::string &function, const std::string &file);

std::ostream &LogSimple(LogType logType) ;

std::ostream &LogFunc(LogType logType);

std::ostream &sysLog(LogType logType, const int line, const std::string &function, const std::string &file);

std::ostream &sysLogSimple(LogType logType) ;

std::ostream &sysLogFunc(LogType logType);

#define LOG \
Log(LogType::NORMAL, __LINE__,__FUNCTION__,__FILE__)

#define LOG_SIMPLE \
LogSimple(LogType::SIMPLE)

#define  LOG_FUNC \
LogFunc(LogType::FUNC)

#define SYS_LOG \
sysLog(LogType::NORMAL, __LINE__,__FUNCTION__,__FILE__)

#define SYS_LOG_SIMPLE \
sysLogSimple(LogType::SIMPLE)

#define  SYS_LOG_FUNC \
sysLogFunc(LogType::FUNC)


#endif //TEST_LOGGER_H
