//
// Created by rrzhang on 2020/3/22.
//
#include <string.h>
#include <iostream>
#include "file_system.h"

using namespace std;

int main() {


    int fd = FileSystem::OpenFile("test");
    cout << fd << endl;
    char buf[10];
    memset(buf, 1, 10);
    for (int i = 0; i < 10; i++) {
        memset(buf, i + 65, 10);
        FileSystem::Pwrite(fd, buf, 10, i*10);
    }

    for (int i = 0; i < 10; i++) {
        memset(buf, 0, 10);
        FileSystem::Pread(fd, buf, 10, i * 10);
        std::string string1(buf, 10);
        cout << string1 << endl;
    }

    FileSystem::Close(fd);
    return 0;
}