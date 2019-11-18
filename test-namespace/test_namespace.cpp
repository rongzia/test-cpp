//
// Created by rrzhang on 2019/11/12.
//

#include <iostream>

using namespace std;

namespace { int i = 256; }

namespace ns {

    namespace { int i = 128; }

    void func(void) {
        cout << "ns::func :" << endl;
        cout << "\t::i=" << ::i << endl;
        cout << "\tns::i=" << i << endl;
    }

}

int main(void) {
    cout << ::i << endl;
    cout << "i=" << i << endl;
    cout << "ns::i=" << ns::i << endl;
    ns::func();
    return 0;
}