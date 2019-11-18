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
    std::string Logger::path_simple_;
    LogType Logger::logType_;

    void set_path(const std::string path) {
        Logger::path_ = path;
        Logger::path_simple_ = path + "_SAMPLE";
    }

    void Logger::Open() {
        if (!log_file_.is_open()) {
            log_file_.open(LogType::SIMPLE == logType_ ? path_simple_: path_, std::ios::app);
        }
    }

    std::ostream &Logger::GetStream() {
        if ("" == path_) {
            if (nullptr == getenv("MYSQL_DATA_PATH")) {
                path_ = std::string(getenv("HOME")) + "/LOG";
                path_simple_ = std::string(getenv("HOME")) + "/LOG_SAMPLE";
            } else {
                path_ = std::string(getenv("MYSQL_DATA_PATH")) + "/LOG";
                path_simple_ = std::string(getenv("MYSQL_DATA_PATH")) + "/LOG_SAMPLE";
            }
        }

        Open();
#ifdef DEBUG_FLAG
            std::cout << "LOG file opend in : " << (LogType::SIMPLE == logType_ ? path_simple_: path_) << std::endl;
#endif
        return log_file_.is_open() ? log_file_ : std::cout;
    }

    std::ostream &Logger::Log(LogRank log_rank, const int line, const std::string &function, const std::string &file) {
        logType_ = LogType::NORMAL;
        return GetStream() << "[" << getTime() << ", line " << line << ", " << function << "()] ";
    }

    std::ostream &Logger::LogSimple(){
        logType_ = LogType::SIMPLE;
        return GetStream();
    }

    Logger::Logger() {
#ifdef DEBUG_FLAG
        std::cout << "Logger(). ";
        std::cout << (path_ == "" ? "has not set path." : "log file path : " + path_) << std::endl;
#endif
    }

    Logger::~Logger() {
        GetStream() << std::endl; // << std::flush;
        log_file_.close();
#ifdef DEBUG_FLAG
        std::cout << "~Logger(). file " << path_ << " closed." << std::endl;
#endif
    }
}