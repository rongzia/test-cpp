//
// Created by rrzhang on 2019/8/28.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "test_grpc.grpc.pb.h"
#include "performance_api.h"
#include "util/random_string.h"
#include "profiler.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using test_grpc::PutRequest;
using test_grpc::PutReply;
using test_grpc::TestGRpc;


#define PERFORMANCE_WRITE_CLIENT_TIME_1 "CLIENTWriteTime1"
#define PERFORMANCE_WRITE_CLIENT_TIME_2 "CLIENTWriteTime2"

class TestGRpcClient {
public:
    TestGRpcClient(std::shared_ptr<Channel> channel)
            : stub_(TestGRpc::NewStub(channel)) {}

    std::string Put(std::string str) {
        PutRequest request;
        request.set_str(str);

        PutReply reply;
        ClientContext context;

        Status status = stub_->Put(&context, request, &reply);

        if (status.ok()) {
            return reply.str();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<TestGRpc::Stub> stub_;
};

int main(int argc, char **argv) {
    TestGRpcClient testGRpcClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));


    std::string str;
    std::string result;
    RandNum_generator rng(0, 255);
    Profiler profiler;

    profiler.Start();
#ifdef TEST
    for(int i = 0; i< 1; i++){
        str = random_str(rng, 4096);
        result = testGRpcClient.Put(str);
        assert("ack" == result);
    }
#else
    createIndicatior(".",PERFORMANCE_WRITE_CLIENT_TIME_1);
    createIndicatior(".",PERFORMANCE_WRITE_CLIENT_TIME_2);
    for (int i = 0; i < 100000; i++) {
        beginIndicatiorTimeRecord(PERFORMANCE_WRITE_CLIENT_TIME_1);
        str = random_str(rng, 4096);

        beginIndicatiorTimeRecord(PERFORMANCE_WRITE_CLIENT_TIME_2);
        result = testGRpcClient.Put(str);
        endIndicatiorTimeRecord(PERFORMANCE_WRITE_CLIENT_TIME_2);

        assert("ack" == result);
        endIndicatiorTimeRecord(PERFORMANCE_WRITE_CLIENT_TIME_1);
    }
    finishRecord(PERFORMANCE_WRITE_CLIENT_TIME_1);
    finishRecord(PERFORMANCE_WRITE_CLIENT_TIME_2);
#endif

    profiler.End();
    std::cout << "Total time : " << profiler.Elapsed() << std::endl;
    return 0;
}
