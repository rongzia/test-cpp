//
// Created by rrzhang on 2020/4/4.
//
#include <iostream>
#include <fstream>
using namespace std;

int main(){

	std::string line;
	std::ifstream fin(string("/home/zhangrongrong/CLionProjects/test-cpp/other/YCSB_schema.txt"));
    while (getline(fin, line)) {
        if (line.compare(0, 6, "TABLE=") == 0) {
            cout << line.size() << endl;
        }
            cout << line.size() << endl;

    }
    return 0;
}