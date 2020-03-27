//
// Created by rrzhang on 2020/3/22.
//
#include <thread>
#include <iostream>
#include <memory>
#include "profiler.h"

using namespace std;

int main(){
    std::unique_ptr<Profiler> profiler(new Profiler());

    profiler->Start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    profiler->End();

    cout << profiler->Elapsed().Nanos() << endl;
    cout << profiler->Elapsed().Micros() << endl;
    cout << profiler->Elapsed().Millis() << endl;
    cout << profiler->Elapsed().Seconds() << endl;
}