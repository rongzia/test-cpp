#include <iostream>
#include <unistd.h> 
using namespace std;

class A{
public:
    int a;
};

int main(){
    A* a = new A();
    
    pid_t fpid = fork();
    if(fpid < 0) {
        cout << "fork error" << endl;
    } else if(fpid == 0) {
        // 子进程
        a->a = 1;
        cout << "son: addressof(a): " << addressof(a) << ", valueof(a): " << a->a << endl;
    } else {
        a->a = 2;
        cout << "father: addressof(a): " << addressof(a) << ", valueof(a): " << a->a << endl;
    }

    return 0;
}