//
// Created by rrzhang on 2019/9/12.
//

#ifndef COMPARE_GLUSTER_AND_GPRC_STRING_UTIL_H
#define COMPARE_GLUSTER_AND_GPRC_STRING_UTIL_H

#include <stdarg.h>
#include <cstring>
#include <thread>
#include <random>
#include <iostream>

class RandNum_generator
{
private:
    RandNum_generator(const RandNum_generator&) = delete;
    RandNum_generator& operator=(const RandNum_generator&) = delete;
    std::uniform_int_distribution<unsigned> u;
    std::default_random_engine e;
    int mStart, mEnd;
public:
    // [start, end], inclusive, uniformally distributed
    RandNum_generator(int start, int end)
            : u(start, end)
            , e(std::hash<std::thread::id>()(std::this_thread::get_id()))
            , mStart(start), mEnd(end)
    {}

    // [mStart, mEnd], inclusive
    unsigned nextNum()
    {
        return u(e);
    }

    // [0, max], inclusive
    unsigned nextNum(unsigned max)
    {
        return unsigned((u(e) - mStart) / float(mEnd - mStart) * max);
    }
};

class StringUtil {
public:
    static std::string VFormat(const std::string fmt_str, va_list args);
    static std::string random_str(RandNum_generator& rng, std::size_t strLen);
};




#endif //COMPARE_GLUSTER_AND_GPRC_STRING_UTIL_H
