//
// Created by rrzhang on 2019/11/10.
//
#include <glog/logging.h>

int open();

int main(int argc, char *argv[]){
    google::InitGoogleLogging("");
    google::SetLogDestination(google::INFO, "/home/rrzhang/CLionProjects/test/test-glog/LOG_");
    for(int i = 0; i< 10; i++){
        open();
    }
    google::ShutdownGoogleLogging();
}

int open(){


    LOG(INFO)<<" opened";


}