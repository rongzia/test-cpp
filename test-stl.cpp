// #include <iostream>
// #include <map>
// #include <vector>
// using namespace std;

// class A{
// public:
//     A(){cout << "A::A()" << endl;}
//     A(string name): name_(name) { cout << "A::A(), " << name << endl;}
//     A(const A &) {
//         cout << "copy A, " << name_ << endl;
//     }
//     ~A(){
//         cout << "A::~A(), " << name_ << endl;
//     }
//     string name_;
// };
// std::map<int, A*> a_map;
// std::vector<A> a_vector;

// void fun1() {
//     A* a = new A("map0");
//     a_map.insert(make_pair(0, a));
//     cout << "a_map[0]: " << a_map[0] << endl;
//     // delete a;
// }
// void fun2() {
//     A a("push_back");
//     cout << "push_back: ";
//     a_vector.push_back(a);
//     cout << "emplace_back: ";
//     A a2("empalce_back");
//     a_vector.emplace_back(a2);
//     // // cout << "a_vector[0]: " << a_vector->at(0) << endl;
//     // // delete a;
// }

// int main() {
//     /// map 存的是指针，不会进行对象拷贝，仅仅是指针值放进去，同时map删除某个值，或者map清空时，都只会删除一个指针，并不会调用指针指向的析构函数
//     cout << "test ptr..." << endl;
//     fun1();
//     A* temp = a_map[0];
//     a_map.erase(0);
//     a_map.clear();
//     cout << "delete temp: ";
//     delete temp;
//     cout << "end test ptr..." << endl << endl;


//     /// vector 存放对象，而不是对象指针
//     cout << "test object..." << endl;
//     fun2();
//     cout << "end test object..." << endl;
//     /// 最后 a_vector 会清空，造成里面的对象析构

    
//     return 0;
// }

#include <iostream>
#include <cassert>
using namespace std;
class RowItem {
    public:

        RowItem(uint64_t key, size_t size);
        RowItem() = delete;
        RowItem(const RowItem&) = delete;
        RowItem& operator=(const RowItem&) = delete;

        ~RowItem();

        uint64_t key_;
        size_t size_;
        char* row_;
    };
RowItem::RowItem(uint64_t key, size_t size)
            : key_(key)
              , size_(size) {
        if(0 != size_) {
            assert(size_ > 0);
            row_ = new char[size_];
        } else {
            row_ = nullptr;
        }
    }

    RowItem::~RowItem() {
        if(nullptr != row_) {
            delete [] row_;
        }
        size_ = 0;
        row_ = nullptr;
        cout << "RowItem::~RowItem()" << endl;
    }
struct WriteHisEntry {
	bool valid;		// whether the entry contains a valid version
	bool reserved; 	// when valid == false, whether the entry is reserved by a P_REQ 
	RowItem * row;
};
int main() {
WriteHisEntry * _write_history;
_write_history = new WriteHisEntry[4]();
for(int i = 0; i< 4 ;i++) {
    _write_history[i].row = new RowItem(0, 110);
}

delete [] _write_history;

    return 0;
}