//
// Created by rrzhang on 2019/9/12.
//

#ifndef COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H
#define COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H


#include <string>
#include <vector>

class FileSystem {

public:

    static size_t string_len;
    enum class FileFlag {
        RDWR = 02,
        APPEND = 02000
    };


    //!
    static int Seek(int fd, off64_t offset);

    ///
    static std::string FilePath();
    //! 获取目录下文件/文件夹名
    static int GetDirFiles(const std::string &dir, std::vector<std::string> *result);

    //! 获取文件大小
    static int GetFileLength(const std::string &file);

    //! 读取
    static int Read(int fd, char *buf, size_t size);

    static int Read(int fd, size_t size, std::string *value);

    //! 读取固定大小的内容
    static int Read(int fd, std::string *value) {
        return Read(fd, FileSystem::string_len, value);
    }

    //! 读取固定大小的内容，位置由 index 给出
    static int ReadByIndex(int fd, int index, std::string *value){
        Seek(fd, FileSystem::string_len * index);
        return Read(fd, FileSystem::string_len, value);
    }

    //! 写
    static int Write(int fd, const char *buf, size_t size);

    static int Write(int fd, const std::string &value) {
        return Write(fd, value.data(), value.size());
    }

    static bool FileExists(const std::string &path);

    //! 打开或创建文件
    static int OpenFile(const std::string &path, const std::string &name, FileFlag flag = FileFlag::RDWR) {
        OpenFile(path.c_str(), name.c_str());
    }

    static int OpenFile(const char *path, const char *name, FileFlag fileflag = FileFlag::RDWR);

    //! 关闭
    static int Close(int fd);
};
// Hash


#endif //COMPARE_GLUSTER_AND_GPRC_FILE_SYSTEM_H
