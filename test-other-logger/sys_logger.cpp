//
// Created by rrzhang on 2019/11/18.
//
#include "logger.h"

std::ofstream log_file_;
std::string path_;
LogType logType_;

extern std::ostream &GetStream();

std::string getTime() {
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

void init(LogType logType) {
    logType_ = logType;
    if (log_file_.is_open()) {
        GetStream() << std::flush;
        log_file_.close();
#ifdef DEBUG_FLAG
        std::cout << "~Logger(). file " << path_ << " closed." << std::endl;
        std::cout << "log_file_ open ? " << (log_file_.is_open() ? "yes" : "no") << std::endl;
#endif
    }
    path_ = "";

    if (log_file_.is_open()) {
        GetStream() << std::endl << std::flush;
        log_file_.close();
    }
    if ("" == path_) {
        if (nullptr == getenv("MYSQL_DATA_PATH")) {
            path_ = std::string(getenv("HOME"));
        } else {
            path_ = std::string(getenv("MYSQL_DATA_PATH"));
        }
    }
    switch (logType_) {
        case LogType::NORMAL :
            path_ += "/LOG_SYS";
            break;
        case LogType::SIMPLE :
            path_ += "/LOG_SIMPLE_SYS";
            break;
        case LogType::FUNC :
            path_ += "/LOG_FUNC_SYS";
            break;
        default:
            path_ += "/LOG_SYS";
    }

#ifdef DEBUG_FLAG
    std::cout << "Logger(). type:" << (int) logType << std::endl;
    std::cout << (path_ == "" ? "has not set path." : "log file path : " + path_) << std::endl;
#endif
}

void set_path(const std::string path) {
    path_ = path;
}

void open() {
    if (!log_file_.is_open() && "" != path_) {
        log_file_.open(path_, std::ios::app);
#ifdef DEBUG_FLAG
        std::cout << "LOG file opend in : " << path_ << std::endl;
#endif
    }
}

std::ostream &GetStream() {
    open();
    return log_file_.is_open() ? log_file_ : std::cout;
}

std::ostream &sysLog(LogType logType, const int line,
                     const std::string &function, const std::string &file) {
    init(logType);
    return GetStream() << "[" << getTime() << ", line " << line << ", " << function << "()] ";
}

std::ostream &sysLogSimple(LogType logType) {
    init(logType);
    return GetStream();
}

std::ostream &sysLogFunc(LogType logType) {
    init(logType);
    return GetStream();
}



