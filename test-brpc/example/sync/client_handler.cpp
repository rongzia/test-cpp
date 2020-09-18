//
// Created by rrzhang on 2020/5/25.
//


#include <butil/logging.h>
#include "client_handler.h"

#include "config.h"
#include "util/profiler.h"


namespace test_rpc {

    TestClient::TestClient(const std::string &addr) : rpc_time_(ATOMIC_VAR_INIT(0))
                                                      , rpc_count_(ATOMIC_VAR_INIT(0)) {
        brpc::ChannelOptions options;
        options.use_rdma = false;
        if (channel.Init(addr.c_str(), &options) != 0) {
            LOG(ERROR) << "Fail to initialize channel";
        }
        stub_.reset(new test_rpc::TestRpcService_Stub(&channel));
    }

    void TestClient::GetItem(uint64_t key, char *buf, size_t size) {
        test_rpc::GetItemRequest request;
        test_rpc::GetItemReply reply;
        ::brpc::Controller cntl;

        request.set_key(key);

        dbx1000::Profiler profiler;
        profiler.Clear();
        profiler.Start();
        stub_->GetItem(&cntl, &request, &reply, NULL);
        if (cntl.Failed()) {
            LOG(WARNING) << cntl.ErrorText();
        }
        profiler.End();
        assert(!cntl.Failed());
        assert(size == reply.item_size());
        assert(size == reply.item().size());
        memcpy(buf, reply.item().data(), size);

        rpc_time_.fetch_add(profiler.Micros());
        rpc_count_.fetch_add(1);
    }

    void TestClient::Clear() {
        rpc_time_ = 0;
        rpc_count_ = 0;
    }

}