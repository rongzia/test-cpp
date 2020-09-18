//
// Created by rrzhang on 2020/5/25.
//

#include <string>
#include <memory>
#include <thread>
#include <iostream>
#include <vector>
#include "gflags/gflags.h"

#include "config.h"
#include "client_handler.h"
#include "util/profiler.h"

using namespace std;
using namespace test_rpc;

namespace test_rpc {
    DEFINE_int32(RPC_COUNT, 10000, "each thread need call RPC_COUNT times");
    DEFINE_string(ip, "0.0.0.0", "connet to");
}

int main(int argc, char *argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    dbx1000::Profiler profiler;

    /// 多个线程共享一个 channel
    test_rpc::TestClient *testClient;
    testClient = new test_rpc::TestClient(FLAGS_ip + ":" + to_string(FLAGS_SERVER_PORT));

    std::vector<thread> threads;
    for (int num_thread = 2; num_thread < 32; num_thread += 2) {
        {   ///
            threads.clear();
            profiler.Clear();
        }

        /// start threads
        profiler.Start();
        for (int i = 0; i < num_thread; i++) {
            test_rpc::TestClient *temp = testClient;
            int item_size = FLAGS_ITEM_SIZE;
            threads.emplace_back(thread([i, &temp, item_size]() {
                srand(chrono::system_clock::now().time_since_epoch().count());
                for (int i = 0; i < FLAGS_RPC_COUNT; i++) {
                    char buf[item_size];
                    int a = rand() % 10;
                    //  cout << a << " ";
                    temp->GetItem(a, buf, item_size);
                    for (int j = 0; j < item_size; j++) { assert(a + '0' - 0 == buf[j]); }
                }
            }));
        }
        for (auto &th : threads) { th.join(); }

        uint64_t rpc_time = testClient->rpc_time_, rpc_count = testClient->rpc_count_;
        testClient->Clear();

        profiler.End();
        cout << endl;
        cout << "1 process, " << num_thread << " threads, 1 rpc channel: " << endl;
        cout << "total     time  : " << profiler.Micros() << " us." << std::endl;
        cout << "througthput     : " << FLAGS_RPC_COUNT * num_thread / profiler.Seconds() << std::endl;
        cout << "total rpc time  : " << rpc_time << " us." << std::endl;
        cout << "total rpc count : " << rpc_count << std::endl;
        cout << "average   time  : " << rpc_time / rpc_count << " us." << std::endl;

        this_thread::sleep_for(chrono::seconds(2));
    }


    return 0;
}
