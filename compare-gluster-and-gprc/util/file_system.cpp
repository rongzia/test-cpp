//
// Created by rrzhang on 2019/9/12.
//

#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <cerrno>
#include <iostream>

#include "file_system.h"
#include "exception.h"


size_t FileSystem::string_len = 4096;

std::string FileSystem::FilePath(){
    std::string path;
    char buffer[256];
    getcwd(buffer, 256);
    path.assign(buffer, strlen(buffer));
    return path;
}

int FileSystem::GetDirFiles(const std::string &dir, std::vector<std::string> *result) {
    int res = 0;
    result->clear();
    DIR *d = opendir(dir.c_str());
    if (d == NULL) {
        return errno;
    }
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
            continue;
        }
        result->push_back(entry->d_name);
    }
    closedir(d);
    return res;
}

int FileSystem::GetFileLength( const std::string &file) {
    struct stat stat_buf;
    int rc = stat(file.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int FileSystem::Read(int fd, char *buf, size_t size) {
//    std::cout<<"FileSystem::ReadBuf"<<std::endl;
//    cout<<lseek(fd, 0, SEEK_CUR)<<endl;
    if (fd < 0) {
        return -1;
    }

    size_t nleft = size;
    char *pos = buf;

    while (nleft > 0) {
        ssize_t r = read(fd, pos, nleft);
        if (r < 0) {
            if (errno == EINTR) {
                continue;  // Retry
            } else {
                close(fd);
                return -1;
            }
        }
        pos += r;
        nleft -= r;
    }
//    std::cout<< "Read success."<<std::endl;
    return 0;
}

int FileSystem::Read(int fd, size_t size, std::string *value) {
//    std::cout<<"FileSystem::Read"<<std::endl;
    char *buf = new char[size]();
    Read(fd, buf, size);

    (*value).assign(buf, size);
    delete buf;
    return 0;
}

int FileSystem::Write(int fd, const char *buf, size_t size) {
    if (fd < 0) {
        return -1;
    }

    size_t nwrite = size;
    const char *pos = buf;
    while (nwrite > 0) {
        ssize_t w = write(fd, pos, nwrite);
        if (w < 0) {
            if (errno == EINTR) {
                continue;  // Retry
            }
            return -1;
        }
        pos += w;
        nwrite -= w;
    }
    return 0;
}

bool FileSystem::FileExists(const std::string &path) {
    return access(path.c_str(), F_OK) == 0;
}


int FileSystem::OpenFile(const char *path, const char *name, FileFlag fileflag) {
    if (!FileExists(path)
        && 0 != mkdir(path, 0755)) {
        throw IOException("\"%s\":No such directory or can not be created. %s", path, strerror(errno));
    }

    int flag = O_RDWR | O_CREAT;
    std::string open_path(path);
    open_path += "/";
    open_path += name;

    if (FileFlag::APPEND == fileflag) {
        flag |= O_APPEND;
    }
    int fd = open(open_path.c_str(), flag, 0644);

    if (fd < 0) {
        throw IOException("Cannot open file \"%s\": %s", path, strerror(errno));
    }

    return fd;
}

int FileSystem::Close(int fd) {
    if (fd > 0) {
        close(fd);
    }
}

int FileSystem::Seek(int fd, off64_t offset) {
    lseek(fd, offset, SEEK_SET);
}