//
// Created by rrzhang on 2019/11/10.
//

#include <iostream>
#include "my_logger.h"

using namespace std;

int main() {
    initLogger("/home/rrzhang/CLionProjects/test/test-mylog/LOG"
            , "/home/rrzhang/CLionProjects/test/test-mylog/LOG"\
            , "/home/rrzhang/CLionProjects/test/test-mylog/LOG");
    LOG(INFO) << "helloworld";
    LOG(INFO) << "helloworld";
    LOG(INFO) << "helloworld";
    LOG(INFO) << "helloworld";
    LOG(WARNING) << "helloworld";
    LOG(WARNING) << "helloworld";
    LOG(WARNING) << "helloworld";
    LOG(WARNING) << "helloworld";


    return 0;
}