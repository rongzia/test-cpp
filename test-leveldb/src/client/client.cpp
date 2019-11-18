//
// Created by rrzhang on 2019/8/28.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "leveldb/db.h"
#include "leveldb_cs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using leveldb_cs::PutRequest;
using leveldb_cs::PutReply;
using leveldb_cs::GetRequest;
using leveldb_cs::GetReply;
using leveldb_cs::LevelDBCS;

class LevelDBClient {
public:
    LevelDBClient(std::shared_ptr<Channel> channel)
            : stub_(LevelDBCS::NewStub(channel)) {}

    std::string Put(const std::string &key, const std::string &value) {
        PutRequest request;
        request.set_key(key);
        request.set_value(value);

        PutReply reply;
        ClientContext context;

        Status status = stub_->Put(&context, request, &reply);

        if (status.ok()) {
            return reply.status();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }
    std::string Get(const std::string &key, std::string *value) {
        GetRequest request;
        request.set_key(key);

        GetReply reply;
        ClientContext context;

        Status status = stub_->Get(&context, request, &reply);

        if (status.ok()) {
            *value = reply.value();
            return reply.status();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<LevelDBCS::Stub> stub_;
};

int main(int argc, char **argv) {
    LevelDBClient levelDbClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string key("key");
    std::string put_str("something");
    std::string status;
    status = levelDbClient.Put(key, put_str);
    std::cout << "Put result : " << status << std::endl;
    std::cout << "Put value : " << put_str << std::endl;

    std::string get_str;
    status = levelDbClient.Get("key", &get_str);
    std::cout << "Get result : " << status << std::endl;
    std::cout << "Get value : " << get_str << std::endl;

    return 0;
}
