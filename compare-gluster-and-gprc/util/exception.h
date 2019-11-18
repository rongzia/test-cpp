//
// Created by rrzhang on 2019/9/12.
//

#ifndef COMPARE_GLUSTER_AND_GPRC_EXCEPTION_H
#define COMPARE_GLUSTER_AND_GPRC_EXCEPTION_H

#include <stdarg.h>
#include <stdexcept>
using namespace std;

enum class ExceptionType {
    INVALID = 0,          // invalid type
    IO = 28,              // IO exception
};

class Exception : public std::exception {
public:
    Exception(string message);
    Exception(ExceptionType exception_type, string message);

    ExceptionType type;

public:
    const char *what() const noexcept override;

    string ExceptionTypeToString(ExceptionType type);

protected:
    void Format(va_list ap);

private:
    string exception_message_;
};


class IOException : public Exception {
public:
    IOException(string msg, ...);
};

#endif //COMPARE_GLUSTER_AND_GPRC_EXCEPTION_H
