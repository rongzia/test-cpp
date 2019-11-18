//
// Created by rrzhang on 2019/9/12.
//

#include "string_util.h"

std::string StringUtil::VFormat(const std::string fmt_str, va_list args) {
    va_list args_copy;

    char* formatted;
    // make a copy of the args as we can only use it once
    va_copy(args_copy, args);

    // first get the amount of characters we need
    const auto n = vsnprintf(nullptr, 0, fmt_str.c_str(), args) + 1;

    // now allocate the string and do the actual printing
    formatted = new char[n];
    (void)vsnprintf(&formatted[0], n, fmt_str.c_str(), args_copy);
    return std::string(formatted);
}


std::string StringUtil::random_str(RandNum_generator& rng, std::size_t strLen)
{
    std::string rs(strLen, ' ');
    for (auto& ch : rs) {
        ch = rng.nextNum();
    }
    return rs;
}