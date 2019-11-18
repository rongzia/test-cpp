//
// Created by rrzhang on 2019/11/11.
//

#include "logger.h"
#include <iostream>

#define DEBUG_FLAG

namespace logger {

    std::string getTime() {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
        return tmp;
    }

    std::ofstream Logger::log_file_;
    std::string Logger::path_;
    LogType Logger::logType_;

    Logger::Logger(LogType logType) {
        logType_ = logType;
        if ("" == path_) {
            if (nullptr == getenv("MYSQL_DATA_PATH")) {
                path_ = std::string(getenv("HOME"));
            } else {
                path_ = std::string(getenv("MYSQL_DATA_PATH"));
            }
        }
        switch (logType_) {
            case LogType::NORMAL :
                path_ += "/LOG";
                break;
            case LogType::SIMPLE :
                path_ += "/LOG_SIMPLE";
                break;
            case LogType::FUNC :
                path_ += "/LOG_FUNC";
                break;
            default:
                path_ += "/LOG";
        }

#ifdef DEBUG_FLAG
        std::cout << "Logger(). type:" << (int) logType << std::endl;
        std::cout << (path_ == "" ? "has not set path." : "log file path : " + path_) << std::endl;
#endif
    }

    void set_path(const std::string path) {
        Logger::path_ = path;
    }

    void Logger::Open() {
        if (!log_file_.is_open() && "" != path_) {
            log_file_.open(path_, std::ios::app);
#ifdef DEBUG_FLAG
            std::cout << "LOG file opend in : " << path_ << std::endl;
#endif
        }
    }

    std::ostream &Logger::GetStream() {
        Open();
        return log_file_.is_open() ? log_file_ : std::cout;
    }

    std::ostream &Logger::Log(LogRank log_rank, const int line, const std::string &function, const std::string &file) {
        return GetStream() << "[" << getTime() << ", line " << line << ", " << function << "()] ";
    }

    std::ostream &Logger::LogSimple() {
        return GetStream();
    }

    std::ostream &Logger::LogFunc() {
        return GetStream();
    }

    Logger::~Logger() {
        GetStream() << std::endl; // << std::flush;
        if (log_file_.is_open()) {
            log_file_.close();
        }
        path_ = "";
#ifdef DEBUG_FLAG
        std::cout << "~Logger(). file " << path_ << " closed." << std::endl;
#endif
    }
}