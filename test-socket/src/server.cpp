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
#include <thread>
#include <iostream>
#include "performance_api.h"

#define PORT 50051
#define BUFFER_SIZE 4096


// TODO :
//#define FUN_1
//#define FUN_2



int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_sockaddr;//一般是储存地址和端口的。用于信息的显示及存储使用
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);//将一个无符号短整型数值转换为网络字节序，即大端模式(big-endian)　
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机的无符号长整形数转换成网络字节顺序。　

    if (bind(server_socket, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr)) == -1) {
        perror("bind error.");
        exit(1);
    }
    if (listen(server_socket, 5) == -1) {
        perror("listen error.");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    int conn = accept(server_socket, (struct sockaddr *) &client_addr, &length);

    if (conn < 0) {
        perror("connect error.");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    std::string str;

#ifdef FUN_1
#define WRITE_SERVER_TIME_1 "ServerWriteTime1"
#define WRITE_SERVER_TIME_2 "ServerWriteTime2"
    createIndicatior(".",WRITE_SERVER_TIME_1);
    createIndicatior(".",WRITE_SERVER_TIME_2);
    while(1){
        beginIndicatiorTimeRecord(WRITE_SERVER_TIME_1);
        memset(buffer, 0, sizeof(buffer));

        beginIndicatiorTimeRecord(WRITE_SERVER_TIME_2);
        //! read
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0 ) {
            std::cout<<"break."<<std::endl;
            break;
        }
        //! write
        send(conn, buffer, len, 0);
        endIndicatiorTimeRecord(WRITE_SERVER_TIME_2);
//        flushNow_C_API(WRITE_SERVER_TIME_2);
        endIndicatiorTimeRecord(WRITE_SERVER_TIME_1);
//        flushNow_C_API(WRITE_SERVER_TIME_1);
    }
    finishRecord(WRITE_SERVER_TIME_1);
    finishRecord(WRITE_SERVER_TIME_2);
#endif

#ifdef FUN_2
#define SERVER_TOTAL_TIME "ServerTotalTime"
#define SERVER_OTHER_TIME "ServerOtherTime"
    createIndicatior(".",SERVER_TOTAL_TIME);
    createIndicatior(".",SERVER_OTHER_TIME);

    int has_created = 0;
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        //! read
        int len = read(conn, buffer, BUFFER_SIZE);
        beginIndicatiorTimeRecord(SERVER_OTHER_TIME);          //! begin other time
        if(0 == has_created){
            beginIndicatiorTimeRecord(SERVER_TOTAL_TIME);
            has_created = 1;
        }
        str.assign(buffer, len);
        if (std::string::npos != str.find("exit", 0)) {             //! 客户端发送 exit 来让 server 退出
            std::cout << "break." << std::endl;
            endIndicatiorTimeRecord(SERVER_TOTAL_TIME);
            break;
        }

        endIndicatiorTimeRecord(SERVER_OTHER_TIME);         //! end other time
        //! write
        write(conn, str.data(), str.length());
    }
    finishRecord(SERVER_TOTAL_TIME);
    finishRecord(SERVER_OTHER_TIME);
#endif

#ifdef TEST
#define SERVER_TIME "ServerTestTime"
    createIndicatior(".",SERVER_TIME);
    while(1){
        memset(buffer, 0, BUFFER_SIZE);

        beginIndicatiorTimeRecord(SERVER_TIME);
        //! read
        int len = recv(conn, buffer, BUFFER_SIZE, 0);
        if (strcmp(buffer, "exit\n") == 0 ) {
            std::cout<<"break."<<std::endl;
            break;
        }
        //! write
        if(BUFFER_SIZE == len){
            str.assign("ack", 3);
            send(conn, str.data(), str.length(), 0);
        }
        endIndicatiorTimeRecord(SERVER_TIME);
    }
    finishRecord(SERVER_TIME);
#endif

    close(conn);
    close(server_socket);
    return 0;
}