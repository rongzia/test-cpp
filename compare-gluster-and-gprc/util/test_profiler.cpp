//
// Created by rrzhang on 2019/9/15.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <cmath>
#include "profiler.h"

using namespace std;
using namespace chrono;


int main() {


/***********************************/
//    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
//
//    auto elapsed = end - start;     //! 一个时间段
//    cout << "elapsed : " << elapsed.count() << " ns" << endl;
//
//    /// 转微秒
//    std::chrono::microseconds microseconds1 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
//    cout << "微秒 : " << double(microseconds1.count()) << " us" << endl;
//    /// 转毫秒
//    std::chrono::milliseconds milliseconds1 = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
//    cout << "毫秒 : " << double(milliseconds1.count()) << " ms" << endl;
//    /// 转秒
//    std::chrono::seconds seconds1 = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
//    cout << "秒 : " << double(seconds1.count()) << " s" << endl;
//
//    ///
//    double d = (std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed)).count();
//    cout << "纳秒转double : " << d << endl;
//    cout << "秒 : " << d / pow(10, 9) << endl;

/// 不管是什么单位的时间，在 chrono 头文件里都是定义的 int64_t 类型，转换之后会失去精度，比如秒就是整数秒，后面的全部丢失了。
/// 想要输出小数秒，用纳秒（double）除以相应的倍数
/***********************************/

    Profiler profiler;
    profiler.Start();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    profiler.End();
    cout << profiler.Micros() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << profiler.Micros() << endl;


    return 0;
}