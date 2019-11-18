

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "leveldb/db.h"
#include "../protos/leveldb_cs.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using leveldb_cs::PutRequest;
using leveldb_cs::PutReply;
using leveldb_cs::GetRequest;
using leveldb_cs::GetReply;
using leveldb_cs::LevelDBCS;

// Logic and data behind the server's behavior.
class LevelDBServiceImpl final : public LevelDBCS::Service {
public:

    ~LevelDBServiceImpl(){
        delete db_;
        std::cout<<"-- LevelDBServiceImpl() destructed."<<std::endl;
    }
    LevelDBServiceImpl(){
        options_.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options_, "/tmp/test-leveldb", &db_);
        std::cout<<"-- LevelDBServiceImpl() constructed."<<std::endl;
    }

    grpc::Status Put(ServerContext* context, const PutRequest* request,
                    PutReply* reply) override {
        std::string key = request->key();
        std::string value = request->value();

        status_ = db_->Put(leveldb::WriteOptions(), key, value);

        reply->set_status(status_.ToString());
        return grpc::Status::OK;
    }

    grpc::Status Get(ServerContext* context, const GetRequest* request,
                     GetReply* reply) override {
        std::string key = request->key();
        std::string value;
        status_ = db_->Get(leveldb::ReadOptions(), key, &value);

        reply->set_value(value);
        reply->set_status(status_.ToString());
        return grpc::Status::OK;
    }

private:
    leveldb::DB* db_;
    leveldb::Options options_;
    leveldb::Status status_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    LevelDBServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}
