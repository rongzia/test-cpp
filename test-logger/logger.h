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

    enum class LogType{
        NORMAL,
        SIMPLE
    };

    class Logger {

    public:
        Logger();

        ~Logger();

        static void Open();

        static std::ostream &Log(LogRank log_rank, const int line, const std::string &function, const std::string &file);

        static std::ostream &LogSimple();

        static std::string path_;
        static std::string path_simple_;

    private:
//        static void Open();
        static std::ostream &GetStream();

        static std::ofstream log_file_;
        static LogType logType_;
    };

    void set_path(const std::string path);
}

#define LOG(log_rank) \
logger::Logger().Log(log_rank, __LINE__,__FUNCTION__,__FILE__)

#define LOG_SIMPLE \
logger::Logger().LogSimple()

#endif //TEST_LOGGER_H
