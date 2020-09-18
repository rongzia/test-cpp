//
// Created by rrzhang on 2020/8/19.
//
#include <cstdint>
#include <string>
#include <atomic>

#include <brpc/channel.h>
#include <butil/time.h>
#include "helloworld.pb.h"
#include "../flags_def.h"

namespace example {
    namespace helloworld {
        class HellowroldClient {
        public:
            HellowroldClient();

            void Hello();

        private:
            brpc::Channel channel_;
            std::unique_ptr<example::HelloworldService_Stub> stub_;
        };

        HellowroldClient::HellowroldClient() {
            brpc::ChannelOptions options;
            options.use_rdma = false;
            if (channel_.Init((FLAGS_SERVER_IP + ":" + std::to_string(FLAGS_SERVER_PORT)).data(), &options) != 0) {
                LOG(ERROR) << "Fail to initialize channel";
                assert(false);
            }
            stub_.reset(new example::HelloworldService_Stub(&channel_));
        }

        void HellowroldClient::Hello() {
            example::HelloworldRequest request;
            example::HelloworldResponse reply;
            ::brpc::Controller cntl;

            request.set_message("zhang");

            cntl.set_log_id(0);
            cntl.request_attachment().append("client_name");

            stub_->Echo(&cntl, &request, &reply, nullptr);
            if (!cntl.Failed()) {
                LOG(INFO) << "Received response from " << cntl.remote_side()
                          << " to " << cntl.local_side()
                          << ": " << reply.message() << " (attached="
                          << cntl.response_attachment() << ")"
                          << " latency=" << cntl.latency_us() << "us";
            } else {
                LOG(WARNING) << cntl.ErrorText();
            }
        }
    }
}


int main() {
    example::helloworld::HellowroldClient hellowroldClient;
    hellowroldClient.Hello();

    return 0;
}