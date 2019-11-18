//
// Created by rrzhang on 2019/9/12.
//



#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>

#include <grpcpp/grpcpp.h>

#include "test.grpc.pb.h"
#include "file_system.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;


class TestServiceImpl final : public test::Test::Service {
public:

    ~TestServiceImpl(){
        close(fd_);
    }

    TestServiceImpl() {
        char buffer[256];
        getcwd(buffer, 256);
        path_.assign(buffer, strlen(buffer));
        fd_ = FileSystem::OpenFile(path_, "testfile");
        std::cout<<"-- LevelDBServiceImpl() constructed."<<std::endl;
    }

    grpc::Status SetStringLength(ServerContext *context, const test::LengthRequest *request,
            test::LengthReply *reply) override {
        FileSystem::string_len = request->len();
        std::cout<<"string_len : "<<FileSystem::string_len<<std::endl;
        reply->set_rc(0);
        return grpc::Status::OK;
    }

    grpc::Status Seek(ServerContext *context, const test::SeekRequest *request,
            test::SeekReply *reply) override  {
        FileSystem::Seek(fd_, request->offset());
        reply->set_rc(0);
        return grpc::Status::OK;
    }

    grpc::Status Write(ServerContext *context, const test::WriteRequest *request,
                       test::WriteReply *reply) override {
        std::string value = request->content();

        int rc = FileSystem::Write(fd_, value);

        assert(0 == rc);
        reply->set_rc(rc);
        return grpc::Status::OK;
    }

    grpc::Status Read(ServerContext *context, const test::ReadRequest *request,
                      test::ReadReply *reply) override {
        int index = request->index();
        std::string value;
//        int rc = FileSystem::ReadByIndex(fd_, index, &value);
        int rc = FileSystem::Read(fd_, &value);

        reply->set_content(value);
        reply->set_rc(rc);
        return grpc::Status::OK;
    }

private:
    int fd_;
    std::string path_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    TestServiceImpl service;

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
