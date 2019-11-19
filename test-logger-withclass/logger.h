//
// Created by rrzhang on 2019/11/11.
//

#ifndef TEST_LOGGER_H
#define TEST_LOGGER_H


#include <ostream>
#include <fstream>

namespace logger {

    std::string getTime();

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

    class Logger {

    public:
        Logger() = delete;

        Logger(LogType logType);

        ~Logger();

        static std::ostream &Log(LogRank log_rank, const int line,
                                 const std::string &function, const std::string &file);

        static std::ostream &LogSimple();

        static std::ostream &LogFunc();


        static std::string path_;
    private:
        static void Open();

        static std::ostream &GetStream();

        static LogType logType_;
        static std::ofstream log_file_;
    };

    void set_path(const std::string path);
}

#define LOG(log_rank) \
logger::Logger(logger::LogType::NORMAL).Log(log_rank, __LINE__,__FUNCTION__,__FILE__)

#define LOG_SIMPLE \
logger::Logger(logger::LogType::SIMPLE).LogSimple()

#define  LOG_FUNC \
logger::Logger(logger::LogType::FUNC).LogFunc()
#endif //TEST_LOGGER_H
