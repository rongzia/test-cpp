// Copyright (c) 2014 baidu-rpc authors.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// A performance test.

#include <pthread.h>
#include <butil/atomicops.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include <bvar/variable.h>
#include <gflags/gflags.h>
#include "test.pb.h"

DEFINE_int32(port, 8002, "TCP Port of this server");
DEFINE_bool(use_rdma, false, "Use RDMA or not");

butil::atomic<uint64_t> g_cnt(0);
butil::atomic<uint64_t> g_total_cnt(0);
volatile bool g_stop = false;

namespace test {
class PerfTestServiceImpl : public PerfTestService {
public:
    PerfTestServiceImpl() {}
    ~PerfTestServiceImpl() {};

    void Test(google::protobuf::RpcController* cntl_base,
              const PerfTestRequest* request,
              PerfTestResponse* response,
              google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        uint64_t cnt = g_cnt.fetch_add(1, butil::memory_order_relaxed);
        if (cnt % 100000 == 99999) {
            response->set_cpu_usage(bvar::Variable::describe_exposed("process_cpu_usage"));
        } else {
            response->set_cpu_usage("");
        }
        if (request->echo_attachment()) {
            brpc::Controller* cntl =
                static_cast<brpc::Controller*>(cntl_base);
            cntl->response_attachment().append(cntl->request_attachment());
        }
        g_total_cnt.fetch_add(1, butil::memory_order_relaxed);
    }
};
}

void* PrintQPS(void*) {
    uint64_t last = 0;
    while (!g_stop) {
        sleep(1);
        uint64_t tmp = g_total_cnt.load(butil::memory_order_relaxed);
        LOG(INFO) << "QPS: " << (tmp - last) / 1000 << "k";
        last = tmp;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    brpc::Server server;
    test::PerfTestServiceImpl perf_test_service_impl;

    if (server.AddService(&perf_test_service_impl, 
                          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service";
        return -1;
    }

    brpc::ServerOptions options;
    options.use_rdma = FLAGS_use_rdma;
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        return -1;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, PrintQPS, NULL);

    server.RunUntilAskedToQuit();

    g_stop = true;
    pthread_join(tid, NULL);

    return 0;
}
