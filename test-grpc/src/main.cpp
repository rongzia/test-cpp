//
// Created by rrzhang on 2019/8/27.
//

#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"

int main() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/test-leveldb", &db);
    assert(status.ok());

    std::string key = "apple";
    std::string value = "A";
    std::string get;

    leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);

    if (s.ok()) s = db->Get(leveldb::ReadOptions(), key, &get);
    if (s.ok()) std::cout << "读取到的与(key=" << key << ")对应的(value=" << get << ")" << std::endl;
    else std::cout << "读取失败!" << std::endl;
    delete db;
    return 0;
}