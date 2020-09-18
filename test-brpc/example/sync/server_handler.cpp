//
// Created by rrzhang on 2020/5/25.
//

#include <butil/logging.h>
#include <brpc/server.h>
#include "server_handler.h"

#include "lock_service.h"
#include "config.h"
#include "util/profiler.h"

DEFINE_bool(use_lock, true, "weather use lock to get page");

namespace test_rpc {

    void TestRpcServiceImpl::GetItem(::google::protobuf::RpcController* controller,
                       const ::test_rpc::GetItemRequest* request,
                       ::test_rpc::GetItemReply* response,
                       ::google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(controller);

//        LOG(INFO) << "Received request[log_id=" << cntl->log_id()
//                  << "] from " << cntl->remote_side()
//                  << " to " << cntl->local_side()
//                  << ": " << request->key()
//                  << " (attached=" << cntl->request_attachment() << ")";


        dbx1000::Profiler profiler;
        profiler.Start();

        char buf[FLAGS_ITEM_SIZE];
        if(FLAGS_use_lock) {
            service_service_->Get(request->key(), buf, FLAGS_ITEM_SIZE);
        }
        else {
            memset(buf, request->key() + '0' - 0, FLAGS_ITEM_SIZE);
        }
        profiler.End();

        response->set_item(buf, FLAGS_ITEM_SIZE);
        response->set_item_size(FLAGS_ITEM_SIZE);
    }
}