//
// Created by rrzhang on 2020/3/27.
//

/// 该 cpp 测试函数的栈空间何时释放，当函数内的栈对象被传到下层函数/线程里时，是否能正确调用
#include <iostream>
#include <memory>
#include <future>
#include <chrono>
using namespace std;

/// 一个简单的类，包含一个 int 参数
class Sample{
public:
    explicit Sample(int x){
        this->a = x;
        cout << "thread id : " << std::this_thread::get_id() << ", Sample::Sample()" << this->a << endl;
    }

    ~Sample(){
        cout << "thread id : " << std::this_thread::get_id() << ", Sample::~Sample()" << this->a << endl;
    }
    Sample() = delete;
    Sample(const Sample &) = delete;
    Sample &operator=(const Sample &) = delete;

    int Get() const{
        return this->a;
    }

    void Set(int a) {
        this->a = a;
    }

    void Print() const{
        cout << "thread id : " << std::this_thread::get_id() << ", this->a : " << Get() << endl;
    }
private:

    int a;
};

void PrintSample1(Sample *sample){
    /// 睡眠的目的是为了观察调用者 fun() 退出，栈空间释放后，sample 的特性
    std::this_thread::sleep_for(chrono::seconds(1));
    sample->Print();
}
void PrintSample2(std::unique_ptr<Sample> sample){
    /// 睡眠的目的是为了观察调用者 fun() 退出，栈空间释放后，sample 的特性
    std::this_thread::sleep_for(chrono::seconds(1));
    sample->Print();
}

void fun(){
    Sample sample1(1);                                  /// 自动释放
    Sample *sample2 = new Sample(2);                    /// 需要手动释放
    std::unique_ptr<Sample> sample3(new Sample(3)); /// 自动释放

    /// 智能指针 p_sample5 托管对象 sample1，如果不释放 p_sample4 所有权，那么释放时会多次调用 sample1 的析构函数，造成非法指针
//    std::unique_ptr<Sample> p_sample5(&sample1);
//    p_sample5.release();

    /// 在将当前栈空间的 对象(变量或指针) 传递给异步/其他线程 时，对象的声明周期不一样
    /// 当前空间的对象 sample1 会在 fun() 结束时释放，后台线程 thread1 并不能正确使用 sample1
    /// 当前空间的对象指针 sample2 会能正确传递给后台线程 thread2，但是并没有正确释放（调用析构函数）
    /// 当前空间的对象智能指针 sample3 表现出和 sample1 相同的性质，因为在 fun() 结束后，sample3 会被自动删除
    std::thread thread1(PrintSample1, &sample1);                /// 错误
    std::thread thread2(PrintSample1, sample2);                 /// OK，但是 sample2 的空间一直不能释放，或者说需要 PrintSample1 去释放
    std::thread thread3(PrintSample1, sample3.get());           /// 错误，和 sample1 一样
    thread1.detach();
    thread2.detach();
    thread3.detach();
    /// 想要智能指针正确传递到后台线程，可以使用 std::move(), 把托管权传递进去，不然就像上面 sample3 一样，达不到预期效果的。
    std::unique_ptr<Sample> sample4(new Sample(4));     /// OK
    std::thread thread4(PrintSample2, std::move(sample4));
    thread4.detach();
    /// 当 fun() 在此处睡眠时，上面所有的后台线程中的参数都没有被释放空间，都能正常输出
//    std::this_thread::sleep_for(chrono::seconds(2));
}


int main(){
    cout << "before fun." << endl;
    fun();
    cout << "after fun." << endl;

    /// 睡眠的目的，使后台线程 cout 能够正确输出，不然后台线程就会被挂起，cout 并没有输出来
    std::this_thread::sleep_for(chrono::seconds(3));

    cout << "out main." << endl;
    return 0;
}