//
// Created by rrzhang on 2019/9/12.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

#include "file_system.h"

using namespace std;

int main() {


    char buffer[256];
    string path;
    cout << "==========path==========" << endl;
    getcwd(buffer, 256);
    path.assign(buffer, strlen(buffer));
    cout << buffer << endl;

    cout << "==========GetDirFiles==========" << endl;
    std::vector<std::string> result;
    int count = FileSystem::GetDirFiles(path, &result);
    for (auto it : result) {
        cout << it << endl;
    }

    cout << "==========OpenFile==========" << endl;
    int fd = FileSystem::OpenFile(path, "testfile");
    cout << "rc = " << fd << endl;


    string value;
    cout << "==========Write==========" << endl;
    for (int i = 0; i < 10; i++) {
        value.assign(10, 'a' + i);
        cout << "write rc = " << FileSystem::Write(fd, value) << endl;
    }

    cout << "==========Read==========" << endl;
    FileSystem::string_len = 10;

    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < 10; i++) {
        FileSystem::ReadByIndex(fd, i, &value) ;
        cout << value << endl;
    }
    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < 10; i++) {
        FileSystem::Read(fd, &value) ;
        cout << value << endl;
    }
    lseek(fd, 0, SEEK_SET);
    FileSystem::Read(fd, 100, &value);
    cout << value << endl;
    close(fd);

    return 0;
}