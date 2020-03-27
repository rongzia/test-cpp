//
// Created by rrzhang on 2019/9/12.
//

#ifndef COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H
#define COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H


#include <string>
#include <vector>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

class FileSystem {

public:

    //! 获取目录下文件/文件夹名
    static int GetDirFiles(const std::string &dir, std::vector<std::string> *result) {
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

    //!
    static std::string CurrentPath() {
        std::string path;
        char buffer[1024];
        getcwd(buffer, 1024);
        path.assign(buffer, strlen(buffer));
        return path;
    }

    //! 打开或创建文件
    static int OpenFile(const std::string &path, int flag = O_RDWR | O_CREAT) {
        std::string open_path(path);
        if (open_path.find("/") == std::string::npos) {
            open_path = CurrentPath() + "/" + path;
        }

        std::cout << open_path << std::endl;
        int fd = open(open_path.c_str(), flag, 0644);

        if (fd < 0) {
//        throw IOException("Cannot open file \"%s\": %s", open_path.data(), strerror(errno));
        }

        return fd;
    }

    //! 关闭
    static int Close(int fd) {
        if (fd > 0) {
            close(fd);
        }
    }

    //!
    static int Seek(int fd, off64_t offset) {

        lseek(fd, offset, SEEK_SET);
    }

    //! 获取文件大小
    static int GetFileLength(const std::string &file) {
        struct stat stat_buf;
        int rc = stat(file.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;
    }

    //! 读
    static ssize_t Read(int fd, char *buf, size_t size) {
        return read(fd, buf, size);
    }

    static ssize_t Pread(int fd, char *buf, size_t size, off64_t off) {
        return pread(fd, buf, size, off);
    }

    //! 写
    static ssize_t Write(int fd, const char *buf, size_t size) {
        return write(fd, buf, size);
    }

    static ssize_t Pwrite(int fd, const char *buf, size_t size, off64_t off) {
        return pwrite(fd, buf, size, off);
    }

    static bool FileExists(const std::string &path) {
        return access(path.c_str(), F_OK) == 0;
    }

};
// Hash


#endif //COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H
