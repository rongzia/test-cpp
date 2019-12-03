#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <cassert>
#include <iostream>
#include "random_string.h"
#include "performance_api.h"
#include "profiler.h"

#define MYPORT  50051
#define BUFFER_SIZE 4096


//#define FUN_1 1
//#define FUN_2 1

int main()
{
    ///定义sockfd
    int client_socket = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）

    if (connect(client_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect error.");
        exit(1);
    }

    //! 用于存放服务端返回值
    char recvbuf[BUFFER_SIZE];

    std::string str;        //! 发送值
    std::string result;     //! 返回值
    RandNum_generator rng(0, 255);
    Profiler profiler;

    profiler.Start();

    #define FUN_2 1
#ifdef FUN_1
#define WRITE_CLIENT_TIME_1 "ClientWriteTime1"
#define WRITE_CLIENT_TIME_2 "ClientWriteTime2"
    createIndicatior_C_API(".",WRITE_CLIENT_TIME_1);
    createIndicatior_C_API(".",WRITE_CLIENT_TIME_2);
    for(int i = 0; i<100000; i++){
        beginIndicatiorTimeRecord_C_API(WRITE_CLIENT_TIME_1);
        str = random_str(rng, BUFFER_SIZE);
//        str.assign(4096, 'a');

        beginIndicatiorTimeRecord_C_API(WRITE_CLIENT_TIME_2);       //! begin WRITE_CLIENT_TIME_2
        send(client_socket, str.data(), str.length(),0);
        int len = recv(client_socket, recvbuf, sizeof(recvbuf),0);
        endIndicatiorTimeRecord_C_API(WRITE_CLIENT_TIME_2);         //! end WRITE_CLIENT_TIME_2

        result.assign(recvbuf, len);
        assert(str == result);
        memset(recvbuf, 0, sizeof(recvbuf));
        endIndicatiorTimeRecord_C_API(WRITE_CLIENT_TIME_1);
    }
    finishRecord_C_API(WRITE_CLIENT_TIME_1);
    finishRecord_C_API(WRITE_CLIENT_TIME_2);

#elif defined FUN_2
#define CLIENT_TOTAL_TIME "ClientTotalTime"
#define CLIENT_OTHER_TIME "ClientOtherTime"
    createIndicatior_C_API(".",CLIENT_TOTAL_TIME);
    createIndicatior_C_API(".",CLIENT_OTHER_TIME);
    beginIndicatiorTimeRecord_C_API(CLIENT_TOTAL_TIME);
    for(int i = 0; i<100000; i++){

        beginIndicatiorTimeRecord_C_API(CLIENT_OTHER_TIME);
        str = random_str(rng, BUFFER_SIZE);
        endIndicatiorTimeRecord_C_API(CLIENT_OTHER_TIME);

        //! write
        write(client_socket, str.data(), str.length());
        //! read
        int len = read(client_socket, recvbuf, BUFFER_SIZE);

        beginIndicatiorTimeRecord_C_API(CLIENT_OTHER_TIME);
        result.assign(recvbuf, len);
        assert(str == result);
        memset(recvbuf, 0, sizeof(recvbuf));
        endIndicatiorTimeRecord_C_API(CLIENT_OTHER_TIME);
        }
    endIndicatiorTimeRecord_C_API(CLIENT_TOTAL_TIME);
    finishRecord_C_API(CLIENT_TOTAL_TIME);
    finishRecord_C_API(CLIENT_OTHER_TIME);

#elif defined TEST
#define CLIENT_TIME "ClientTestTime"
    createIndicatior(".",CLIENT_TIME);
    for(int i = 0; i<100000; i++){
        str = random_str(rng, BUFFER_SIZE);

        beginIndicatiorTimeRecord(CLIENT_TIME);
        send(client_socket, str.data(), str.length(),0);
        int len = recv(client_socket, recvbuf, sizeof(recvbuf),0);

        result.assign(recvbuf, len);
        assert("ack" == result);
        endIndicatiorTimeRecord(CLIENT_TIME);
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    finishRecord(CLIENT_TIME);
#endif

    str.assign("exit\n", 5);
    send(client_socket, str.data(), str.length(), 0);
    close(client_socket);

    profiler.End();
    std::cout << "Total time : " << profiler.Elapsed() << std::endl;
    return 0;
}