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

        struct AsyncJob {
            brpc::Controller* cntl;
            const example::HelloworldRequest* request;
            example::HelloworldResponse* response;
            google::protobuf::Closure* done;

            void run() {
                brpc::ClosureGuard done_guard(done);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                LOG(INFO) << "Received request[log_id=" << cntl->log_id()
                          << "] from " << cntl->remote_side()
                          << " to " << cntl->local_side()
                          << ": " << request->message()
                          << " (attached=" << cntl->request_attachment() << ")";
                response->set_message(request->message());
            }

            void run_and_delete() {
                run();
                delete this;
            }
        };

        static void* process_thread(void* args) {
            AsyncJob* job = static_cast<AsyncJob*>(args);
            job->run_and_delete();
            return nullptr;
        }

        void HelloworldServiceImpl::Echo(::google::protobuf::RpcController *controller,
                                    const ::example::HelloworldRequest *request,
                                    ::example::HelloworldResponse *response, ::google::protobuf::Closure *done) {
            ::brpc::ClosureGuard done_guard(done);

            AsyncJob* job = new AsyncJob();
            job->cntl = static_cast<brpc::Controller *>(controller);
            job->request = request;
            job->response = response;
            job->done = done;
            bthread_t th;
            CHECK_EQ(0, bthread_start_background(&th, NULL, process_thread, job));
            done_guard.release();
            std::cout << "HelloworldServiceImpl::Echo done." << std::endl;
        }
    }
}

void RunHelloWorldServiceThread(brpc::Server* server, example::helloworld::HelloworldServiceImpl* helloworldService){

    if (server->AddService(helloworldService, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(FATAL) << "Fail to add service";
    }

    brpc::ServerOptions options;
    options.use_rdma = false;
    if (server->Start(std::stoi(std::to_string(example::FLAGS_SERVER_PORT)), &options) != 0) {
        LOG(FATAL) << "Fail to start EchoServer";
    }
}

int main(){
    brpc::Server server;
    example::helloworld::HelloworldServiceImpl helloworldService;
    std::thread helloWorldServiceThread(RunHelloWorldServiceThread, &server, &helloworldService);
    helloWorldServiceThread.detach();


    while (1) { std::this_thread::yield(); }
    return 0;
}