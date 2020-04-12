//
// Created by rrzhang on 2020/4/4.
//

/// 在读dbx10000时，遇到这样的代码：
/**
	pthread_t p_thds[g_init_parallelism - 1]; //! p_thds[39]
	for (UInt32 i = 0; i < g_init_parallelism - 1; i++)
		pthread_create(&p_thds[i], NULL, threadInitTable, this);    //! 创建线程
	threadInitTable(this);

	for (uint32_t i = 0; i < g_init_parallelism - 1; i++) {
		int rc = pthread_join(p_thds[i], NULL);
	}
*/
/// 这里的 for 是否有用？

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "../util/profiler.h"

using namespace std;

void wait(){
    std::this_thread::sleep_for(chrono::seconds(1));
}

int main() {

    std::unique_ptr<Profiler> profiler(new Profiler());
    profiler->Start();
    vector<thread> v_thread;
    for(int i = 0; i< 10; i++) {
        v_thread.push_back(thread(wait));
    }
    for(int i = 0; i<10; i++){
        v_thread[i].join();
    }
    profiler->End();
    cout << profiler->Millis() << endl;


    profiler->Start();
    thread thread1(wait);
    thread1.join();
    thread thread2(wait);
    thread2.join();
    thread thread3(wait);
    thread3.join();
    thread thread4(wait);
    thread4.join();
    thread thread5(wait);
    thread5.join();
    profiler->End();
    cout << profiler->Millis() << endl;


    return 0;
}