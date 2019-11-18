//
// Created by rrzhang on 2019/9/15.
//
#include <iostream>
#include <cassert>
#include <map>
#include <random>
#include "file_system.h"
#include "profiler.h"
#include "string_util.h"

enum class ReadFlag {
    READ = 0,
    READBYINDEX = 1,
    RANDOMREAD = 2
};

void Write(int fd, int log, int num, std::map<std::string, double> &times) {
    Profiler write_time;
    Profiler generator_string_time;
    Profiler total_time;
    std::string value;
    RandNum_generator rng(0, 255);
    value = StringUtil::random_str(rng, FileSystem::string_len);

    total_time.Start();
    for (int i = 0; i < num; i++) {

        generator_string_time.Start();

        generator_string_time.Suspend();

        write_time.Start();             //! 写文件开始计时
        int rc = FileSystem::Write(fd, value);
        write_time.Suspend();           //! 写文件暂停计时

        assert(0 == rc);
    }
    total_time.End();

    FileSystem::Write(log, "\t"
                           + std::to_string(write_time.Seconds()) + "\t"
                           + std::to_string(generator_string_time.Seconds()) + "\t"
                           + std::to_string(total_time.Seconds()) + "\t\n");

    times["total_write"] += write_time.Seconds();
    times["total_gen"] += generator_string_time.Seconds();
    times["total"] += total_time.Seconds();
}

void Read(int fd, int log, int num, std::map<std::string, double> &times, ReadFlag flag) {
    Profiler read_time;
    Profiler total_time;
    std::string value;
    RandNum_generator rng(0, 255);

    total_time.Start();
    int rc = 0;
    if (ReadFlag::READ == flag) {
        FileSystem::Seek(fd, 0);
    }
    for (int i = 0; i < num; i++) {
        read_time.Start();             //! 写文件开始计时

        switch (flag) {
            case ReadFlag::READ:
                rc = FileSystem::Read(fd, &value);
                break;
            case ReadFlag::READBYINDEX:
                rc = FileSystem::ReadByIndex(fd, i, &value);
                break;
            case ReadFlag::RANDOMREAD:
                std::default_random_engine e;
                rc = FileSystem::ReadByIndex(fd, e() % num, &value);
                break;
        }
        read_time.Suspend();           //! 写文件暂停计时

        assert(0 == rc);
    }
    total_time.End();

    FileSystem::Write(log, "\t"
                           + std::to_string(read_time.Seconds()) + "\t"
                           + std::to_string(total_time.Seconds()) + "\t\n");

    times["total_raed"] += read_time.Seconds();
    times["total"] += total_time.Seconds();
}

int main() {

    //! 读写文件
    std::string path("/home/rrzhang/share-storage/mnt");
    int fd = FileSystem::OpenFile(path, "testfile");
    FileSystem::string_len = 4096;

    int log = FileSystem::OpenFile(".", "LOG_gluster");     //! log 文件

    int rw_num = 10;           //! 读写循环次数
    int rw_count = 10000;        //! 读写 item 个数


    /// 用于记录总时延
    std::map<std::string, double> times;

    //! 读
    FileSystem::Write(log, "write=======\n\twrite time\tgen time\ttotal time\n");
    for (int i = 0; i < rw_num; i++) {
        Write(fd, log, rw_count, times);
    }
    FileSystem::Write(log, "total : " + std::to_string(times["total_write"]) + "\t"
                           + std::to_string(times["total_gen"]) + "\t"
                           + std::to_string(times["total"]) + "\t\n");


//    std::cout << "path : " << FileSystem::FilePath() << std::endl;
    std::cout << "File size : " << FileSystem::GetFileLength(path + "/testfile") << std::endl;

    /// 顺序读
    times.clear();
    FileSystem::Write(log, "sequetial read=======\n\tread time\ttotal time\n");
    for (int i = 0; i < rw_num; i++) {
        Read(fd, log, rw_count, times, ReadFlag::READ);
    }
    FileSystem::Write(log, "total : " + std::to_string(times["total_raed"]) + "\t"
                           + std::to_string(times["total"]) + "\t\n");


    /// 随机读
    times.clear();
    FileSystem::Write(log, "random read=======\n\tread time\ttotal time\n");
    for (int i = 0; i < rw_num; i++) {
        Read(fd, log, rw_count, times, ReadFlag::RANDOMREAD);
    }
    FileSystem::Write(log, "total : " + std::to_string(times["total_raed"]) + "\t"
                           + std::to_string(times["total"]) + "\t\n");

    return 0;
}