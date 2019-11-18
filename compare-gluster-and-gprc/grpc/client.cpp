//
// Created by rrzhang on 2019/9/12.
//

//
// Created by rrzhang on 2019/8/28.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "test.grpc.pb.h"
#include "profiler.h"
#include "string_util.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using test::WriteRequest;
using test::WriteReply;
using test::ReadRequest;
using test::ReadReply;
using test::LengthRequest;
using test::LengthReply;
using test::SeekRequest;
using test::SeekReply;

static int string_len = 4096;

class TestClient {
public:
    TestClient(std::shared_ptr<Channel> channel)
            : stub_(test::Test::NewStub(channel)) {}


    int SetStringLength(int len) {
        LengthRequest request;
        LengthReply reply;
        ClientContext context;

        request.set_len(len);
        Status status = stub_->SetStringLength(&context, request, &reply);

        if (status.ok()) {
            return reply.rc();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

    int Seek(off64_t offset) {
        SeekRequest request;
        SeekReply reply;
        ClientContext context;

        request.set_offset(offset);
        Status status = stub_->Seek(&context, request, &reply);

        if (status.ok()) {
            return reply.rc();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }

    }

    int Write(const std::string &content) {
        WriteRequest request;
        WriteReply reply;
        ClientContext context;

        request.set_content(content);
        Status status = stub_->Write(&context, request, &reply);

        if (status.ok()) {
            return reply.rc();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

    int Read(int index, std::string *value) {
        ReadRequest request;
        ReadReply reply;
        ClientContext context;

        request.set_index(index);
        Status status = stub_->Read(&context, request, &reply);

        if (status.ok()) {
            *value = reply.content();
            return reply.rc();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<test::Test::Stub> stub_;
};

int main(int argc, char **argv) {
    TestClient testClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));


    testClient.SetStringLength(4096);
    int rw_num = 100000;

    Profiler random_time;
    Profiler grpc_time;
    Profiler total_time;

    std::string value;
    RandNum_generator rng(0, 255);
    total_time.Start();
    for (int i = 0; i < rw_num; i++) {
        random_time.Start();
        value = StringUtil::random_str(rng, string_len);
//        value.assign(10, 'a' + i);
        random_time.End();
        grpc_time.Start();
        int rc = testClient.Write(value);
        grpc_time.End();
        assert(0 == rc);
    }
    std::cout<< "Total write "<< rw_num << " items"<<std::endl;
    std::cout << "write random time : " << random_time.Seconds() << " seconds" << std::endl;
    std::cout << "write grpc time   : " << grpc_time.Seconds() << " seconds" << std::endl;
    std::cout << "write total time  : " << total_time.Seconds() << " seconds" << std::endl;


    testClient.Seek(0);

    grpc_time.Clear();
    total_time.Clear();
    total_time.Start();
    for (int i = 0; i < rw_num; i++) {
        grpc_time.Start();
        int rc = testClient.Read(i, &value);
//        std::cout << "value : " << value << std::endl;
        grpc_time.Suspend();
        assert(0 == rc);
    }
    std::cout<< "Total read "<< rw_num << " items"<<std::endl;
    std::cout << "read grpc time   : " << grpc_time.Seconds() << " seconds" << std::endl;
    std::cout << "read total time  : " << total_time.Seconds() << " seconds" << std::endl;

    return 0;
}
