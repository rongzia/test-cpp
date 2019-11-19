//
// Created by rrzhang on 2019/11/11.
//

#include <iostream>
#include "logger.h"

int main() {

//    logger::set_path(std::string(getenv("HOME")) + "/LOG2");
    LOG(logger::LogRank::INFO) << "NORMAL" << " NORMAL" << " NORMAL" ;
    std::cout << std::endl;
    LOG_SIMPLE << "simple" << " simple" << " simple";
    std::cout << std::endl;
    LOG(logger::LogRank::INFO) << "NORMAL" << " NORMAL" << " NORMAL" ;
    std::cout << std::endl;
    LOG_SIMPLE << "simple" << " simple" << " simple";
    std::cout << std::endl;
    LOG_FUNC << "FUNC" << " FUNC" << " FUNC";
    return 0;
}