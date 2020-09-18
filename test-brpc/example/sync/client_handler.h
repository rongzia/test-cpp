//
// Created by rrzhang on 2020/5/25.
//

#ifndef TEST_RPC_CLIENT_HANDLE_H
#define TEST_RPC_CLIENT_HANDLE_H
#include <cstdint>
#include <string>
#include <atomic>

#include <brpc/channel.h>
#include <butil/time.h>
#include "api.pb.h"

namespace test_rpc {
    class TestClient {
    public:
        TestClient(const std::string &);
        void GetItem(uint64_t key, char *buf, size_t size);

        void Clear();

        std::atomic<uint64_t> rpc_time_;
        std::atomic<uint64_t> rpc_count_;

    private:
        brpc::Channel channel;
        std::unique_ptr <test_rpc::TestRpcService_Stub> stub_;
    };
}
#endif //TEST_RPC_CLIENT_HANDLE_H
