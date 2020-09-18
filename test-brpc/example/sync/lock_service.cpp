//
// Created by rrzhang on 2020/7/22.
//

#include <cassert>
#include <string.h>
#include "lock_service.h"

namespace test_rpc {
    void LockService::Get(uint64_t item_id, char *item, size_t size){
        array_[item_id].mtx.lock();
        assert(item != nullptr);

        memset(item, item_id + '0' - 0, size);
        array_[item_id].mtx.unlock();
    }
}