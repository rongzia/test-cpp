//
// Created by rrzhang on 2020/8/19.
//
#include <cstdint>
#include <string>
#include <atomic>
#include <memory>
#include <thread>

#include <brpc/channel.h>
#include <brpc/parallel_channel.h>
#include <butil/time.h>
#include "helloworld.pb.h"
#include "../flags_def.h"

namespace example {
    namespace helloworld {

        class OnRPCDone;

        class HellowroldClient {
        public:
            HellowroldClient();
            void SyncHello();
            void AsyncHello(OnRPCDone* done);

//        private:
            brpc::Channel channel_;
            std::unique_ptr<example::HelloworldService_Stub> stub_;
            std::atomic<uint64_t> count_;
        };


        class OnRPCDone: public google::protobuf::Closure {
        public:
            void Run() {
                std::unique_ptr<OnRPCDone> self_guard(this);
                if (cntl.Failed()) {
                    LOG(FATAL) << cntl.ErrorText();
                } else {
                    LOG(INFO) << "Received response from " << cntl.remote_side()
                              << " to " << cntl.local_side()
                              << ": " << response.message() << " (attached="
                              << cntl.response_attachment() << ")"
                              << " latency=" << cntl.latency_us() << "us";
                    hellowroldClient->count_.fetch_add(1);
                }
            }

            HelloworldResponse response;
            brpc::Controller cntl;
            HellowroldClient *hellowroldClient;
        };

        HellowroldClient::HellowroldClient() {
            count_ = ATOMIC_VAR_INIT(0);
            brpc::ChannelOptions options;
            options.use_rdma = false;
            if (channel_.Init((FLAGS_SERVER_IP + ":" + std::to_string(example::FLAGS_SERVER_PORT)).data(), &options) != 0) {
                LOG(ERROR) << "Fail to initialize channel";
                assert(false);
            }
            stub_.reset(new example::HelloworldService_Stub(&channel_));
        }

        void HellowroldClient::SyncHello() {
            example::HelloworldRequest request;
            example::HelloworldResponse reply;
            ::brpc::Controller cntl;

            request.set_message(std::to_string(count_.fetch_add(1)));

            cntl.set_timeout_ms(2000);
            stub_->Echo(&cntl, &request, &reply, nullptr);
            if (!cntl.Failed()) {
                LOG(INFO) << "Received response from " << cntl.remote_side()
                          << " to " << cntl.local_side()
                          << ": " << reply.message() << " (attached="
                          << cntl.response_attachment() << ")"
                          << " latency=" << cntl.latency_us() << "us";
            } else {
                LOG(FATAL) << cntl.ErrorText();
            }
            std::cout << "HellowroldClient::SyncHello() done." << std::endl;
        }

        void HellowroldClient::AsyncHello(OnRPCDone* done) {
            example::HelloworldRequest request;
            request.set_message(std::to_string(count_.load()));

            done->hellowroldClient = this;
            done->cntl.set_timeout_ms(2000);
            stub_->Echo(&done->cntl, &request, &done->response, done);
            std::cout << "HellowroldClient::AsyncHello() done." << std::endl;
        }
    }
}


int main() {
    example::helloworld::HellowroldClient hellowroldClient;
    hellowroldClient.SyncHello();


    example::helloworld::OnRPCDone* done1 = new example::helloworld::OnRPCDone();
    example::helloworld::OnRPCDone* done2 = new example::helloworld::OnRPCDone();
    hellowroldClient.AsyncHello(done1);
    hellowroldClient.AsyncHello(done2);

    brpc::Join(done1->cntl.call_id());
    brpc::Join(done2->cntl.call_id());

    std::cout << hellowroldClient.count_.load() << std::endl;

    while(1) {}
    return 0;
}