#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "../pb/os_rpc.grpc.pb.h"

extern "C" {
#include "os_rpc.c"
};

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


class OSRPCServiceImpl final : public osrpc::OSRPC::Service {
    Status RPCInit(ServerContext *context, const osrpc::InitRequest *request,
                   osrpc::InitReply *reply) override {

        char* rc = RPC_Init();
        std::string str;
        str.assign(rc, sizeof(rc));

        reply->set_rc(str);
        return Status::OK;
    }
    Status RPCOpen(ServerContext *context, const osrpc::OpenRequest *request,
                   osrpc::OpenReply *reply) override {
//        int rc = client::RPCOpen();

    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    OSRPCServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char **argv) {
    RunServer();

    return 0;
}
