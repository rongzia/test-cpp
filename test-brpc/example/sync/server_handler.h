//
// Created by rrzhang on 2020/5/25.
//

#ifndef TEST_RPC_SERVER_HANDLER_H
#define TEST_RPC_SERVER_HANDLER_H

#include "api.pb.h"

namespace test_rpc {
    class LockService;

    class TestRpcServiceImpl : public TestRpcService {
    public:
        TestRpcServiceImpl() {};
        virtual ~TestRpcServiceImpl() {};
        virtual void GetItem(::google::protobuf::RpcController* controller,
                       const ::test_rpc::GetItemRequest* request,
                       ::test_rpc::GetItemReply* response,
                       ::google::protobuf::Closure* done);

        LockService* service_service_;
    };
}
#endif //TEST_RPC_SERVER_HANDLER_H
