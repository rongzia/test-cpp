//
// Created by rrzhang on 2019/9/12.
//
#include "exception.h"
#include "string_util.h"

#define FORMAT_CONSTRUCTOR(msg)                                                                                        \
	va_list ap;                                                                                                        \
	va_start(ap, msg);                                                                                                 \
	Format(ap);                                                                                                        \
	va_end(ap);


Exception::Exception(string message) : std::exception(), type(ExceptionType::INVALID) {
    exception_message_ = message;
}

Exception::Exception(ExceptionType exception_type, string message) : std::exception(), type(exception_type) {
    exception_message_ = ExceptionTypeToString(exception_type) + ": " + message;
}

const char *Exception::what() const noexcept {
    return exception_message_.c_str();
}

string Exception::ExceptionTypeToString(ExceptionType type) {
    switch (type) {
        case ExceptionType::INVALID:
            return "Invalid";
        case ExceptionType::IO:
            return "IO";
        default:
            return "Unknown";
    }
}

void Exception::Format(va_list ap) {
    exception_message_ = StringUtil::VFormat(exception_message_, ap);
}


IOException::IOException(string msg, ...) : Exception(ExceptionType::IO, msg) {
    FORMAT_CONSTRUCTOR(msg);
}