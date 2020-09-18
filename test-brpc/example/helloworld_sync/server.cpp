//
// Created by rrzhang on 2020/8/19.
//

#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include <thread>
#include <chrono>
#include "helloworld.pb.h"
#include "../flags_def.h"

namespace example {
    namespace helloworld {
        class HelloworldServiceImpl : public HelloworldService {
        public:
            HelloworldServiceImpl() {}

            virtual ~HelloworldServiceImpl() {}

            virtual void Echo(::google::protobuf::RpcController *controller, const ::example::HelloworldRequest *request,
                 ::example::HelloworldResponse *response, ::google::protobuf::Closure *done);
        };

        void HelloworldServiceImpl::Echo(::google::protobuf::RpcController *controller,
                                    const ::example::HelloworldRequest *request,
                                    ::example::HelloworldResponse *response, ::google::protobuf::Closure *done) {
            // This object helps you to call done->Run() in RAII style. If you need
            // to process the request asynchronously, pass done_guard.release().
            ::brpc::ClosureGuard done_guard(done);

            brpc::Controller *cntl = static_cast<brpc::Controller *>(controller);

            // The purpose of following logs is to help you to understand
            // how clients interact with servers more intuitively. You should
            // remove these logs in performance-sensitive servers.
            LOG(INFO) << "Received request[log_id=" << cntl->log_id()
                      << "] from " << cntl->remote_side()
                      << " to " << cntl->local_side()
                      << ": " << request->message()
                      << " (attached=" << cntl->request_attachment() << ")";

            // Fill response.
            response->set_message(request->message());

            // You can compress the response by setting Controller, but be aware
            // that compression may be costly, evaluate before turning on.
            // cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);

            // Set attachment which is wired to network directly instead of
            // being serialized into protobuf messages.
            cntl->response_attachment().append(cntl->request_attachment());
        }
    }
}

void RunHelloWorldServiceThread(){

    brpc::Server server;
    example::helloworld::HelloworldServiceImpl helloworldService;

    if (server.AddService(&helloworldService, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service";
        assert(false);
    }

    brpc::ServerOptions options;
    options.use_rdma = true;
    if (server.Start((example::FLAGS_SERVER_IP + ":" + std::to_string(example::FLAGS_SERVER_PORT)).data(), &options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        assert(false);
    }
    while(1){}
//    server.RunUntilAskedToQuit();
}

int main(){
    std::thread helloWorldServiceThread(RunHelloWorldServiceThread);
//    RunHelloWorldServiceThread();
    helloWorldServiceThread.detach();


    while (1) {
        std::cout << "test" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}