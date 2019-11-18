

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "test_grpc.grpc.pb.h"
#include "util/random_string.h"
#include "performance_api.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using test_grpc::PutRequest;
using test_grpc::PutReply;
using test_grpc::TestGRpc;

#define PERFORMANCE_WRITE_SERVER_TIME_1 "SERVERWriteTime1"
#define PERFORMANCE_WRITE_SERVER_TIME_2 "SERVERWriteTime2"

// Logic and data behind the server's behavior.
class TestGRpcImpl final : public TestGRpc::Service {
public:

    ~TestGRpcImpl(){
        std::cout<<"-- LevelDBServiceImpl() destructed."<<std::endl;
    }
    TestGRpcImpl(){
        std::cout<<"-- LevelDBServiceImpl() constructed."<<std::endl;
    }

    grpc::Status Put(ServerContext* context, const PutRequest* request,
                    PutReply* reply) override {

        beginIndicatiorTimeRecord_C_API(PERFORMANCE_WRITE_SERVER_TIME_1);
        std::string str = request->str();


        beginIndicatiorTimeRecord_C_API(PERFORMANCE_WRITE_SERVER_TIME_2);
        reply->set_str("ack");
        endIndicatiorTimeRecord_C_API(PERFORMANCE_WRITE_SERVER_TIME_2);
        flushNow_C_API(PERFORMANCE_WRITE_SERVER_TIME_2);

        endIndicatiorTimeRecord_C_API(PERFORMANCE_WRITE_SERVER_TIME_1);
        flushNow_C_API(PERFORMANCE_WRITE_SERVER_TIME_1);
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    TestGRpcImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {

    createIndicatior_C_API(".",PERFORMANCE_WRITE_SERVER_TIME_1);
    createIndicatior_C_API(".",PERFORMANCE_WRITE_SERVER_TIME_2);

    RunServer();

    return 0;
}
