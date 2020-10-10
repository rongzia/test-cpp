#include <iostream>
using namespace std;
 
class A{
    int num;
public:
    A(){
        cout<<"A's constructor"<<endl;
    }
 
    ~A(){
        cout<<"~A"<<endl;
    }
    void show(){
        cout<<"num: "<<num<<endl;
    }
};
 
int main() {
    char mem[100];
    mem[0]='A';
    mem[1]='\0';
    mem[2]='\0';
    mem[3]='\0';
    cout<<(void*)mem<<endl;

    A* p=new (mem) A;
    cout<<p<<endl;
    p->show();
    // delete p;        /// 会把 men 空间直接还给系统，程序退出时，mem 对象也要释放，但是这个地址已经被释放了，会产生段错误
    p->~A();
    
    
    return 0;
}