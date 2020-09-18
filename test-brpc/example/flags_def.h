//
// Created by rrzhang on 2020/9/4.
//

#ifndef TEST_BRPC_FLAGS_DEF_H
#define TEST_BRPC_FLAGS_DEF_H

#include <gflags/gflags.h>
namespace example {
        DECLARE_string(SERVER_IP);
        DECLARE_int32(SERVER_PORT);
}


#endif //TEST_BRPC_FLAGS_DEF_H
