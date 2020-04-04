//
// Created by rrzhang on 2020/3/27.
//


/// 测试 auto 及自动识别变量类型
#include <iostream>

using namespace std;

int main(){

    /// 声明一个 auto 类型，自动解析成 int
    auto a = 1;
    /// 在不知道 a 的类型情况下，声明和 a 同等类型的变量，也可以用在 iter 中
    decltype(a) b = 3.0;

    /// 输出变量的类型
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    return 0;
}