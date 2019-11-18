//
// Created by rrzhang on 2019/11/11.
//

#include <iostream>
#include "logger.h"

int main() {

//    logger::set_path(std::string(getenv("HOME")) + "/LOG2");

//    LOG << "NORMAL" << " NORMAL" << " NORMAL" << std::endl;
//    std::cout << std::endl;
//    LOG << "NORMAL" << " NORMAL" << " NORMAL" << std::endl;
//    std::cout << std::endl;
//    LOG_SIMPLE << "simple" << " simple" << " simple";
//    std::cout << std::endl;
//    LOG_FUNC << "FUNC" << " FUNC" << " FUNC";
//
//    LOG(LogRank::INFO) << "NORMAL" << " NORMAL" << " NORMAL" ;
//    std::cout << std::endl;
//    LOG_SIMPLE << "simple" << " simple" << " simple";
//    std::cout << std::endl;
//    LOG_FUNC << "FUNC" << " FUNC" << " FUNC";

    SYS_LOG << "NORMAL" << " NORMAL" << " NORMAL" << std::endl;
    std::cout << std::endl;
    SYS_LOG << "NORMAL" << " NORMAL" << " NORMAL" << std::endl;
    std::cout << std::endl;

    return 0;
}