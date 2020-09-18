//
// Created by rrzhang on 2020/7/22.
//

#ifndef TEST_RPC_SERVER_SERVICE_H
#define TEST_RPC_SERVER_SERVICE_H

#include <mutex>
#include <array>

namespace test_rpc {

    class ItemNode {
    public:
//        ItemNode();
        std::mutex mtx;
    };

    class LockService {
    public:
        void Get(uint64_t item_id, char *item, size_t size);
        std::array<ItemNode, 10> array_;
    };
}


#endif //TEST_RPC_SERVER_SERVICE_H
