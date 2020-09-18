//
// Created by rrzhang on 2020/5/25.
//
#include <string>
#include <memory>
#include <thread>
#include <iostream>
#include <brpc/server.h>
#include "api.pb.h"
#include "server_handler.h"
#include "lock_service.h"
#include "config.h"

using namespace std;
using namespace test_rpc;


void RunServer(test_rpc::LockService *lockService) {
    brpc::Server server;
    test_rpc::TestRpcServiceImpl test_rpc_service_impl;

    test_rpc_service_impl.service_service_ = lockService;
    if (server.AddService(&test_rpc_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service";
        assert(false);
    }
    brpc::ServerOptions options;
    options.use_rdma = false;
    if (server.Start(FLAGS_SERVER_PORT, &options) != 0) {
        LOG(FATAL) << "Fail to start EchoServer";
    }
    server.RunUntilAskedToQuit();
}


int main() {
    test_rpc::LockService *lockService = new test_rpc::LockService();
        RunServer(lockService);
//        std::thread server(RunServer, host, lockService);
//        server.detach();

//    while (1) {this_thread::yield();}
    return 0;
}

