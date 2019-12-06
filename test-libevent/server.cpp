/**
 * Created by rrzhang on 2019/12/2.
 */
#include <iostream>
#include <cstring>

#include<netinet/in.h>
#include<sys/socket.h>

#include<event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>


void listener_cb(evconnlistener *listener, evutil_socket_t fd,
                 struct sockaddr *sock, int socklen, void *arg);

void read_cb(bufferevent *bev, void *arg);

void error_cb(bufferevent *bev, short events, void *arg);

int main() {
//    evthread_use_pthreads();//enable threads

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8989);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    event_base *base = event_base_new();
    evconnlistener *listener = evconnlistener_new_bind(base, listener_cb, base,
                                                       LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE | LEV_OPT_THREADSAFE,
                                                       10, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));

    event_base_dispatch(base);
    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}


//有新的客户端连接到服务器
//当此函数被调用时，libevent已经帮我们accept了这个客户端。该客户端的
//文件描述符为fd
void listener_cb(evconnlistener *listener, evutil_socket_t fd,
                 struct sockaddr *sock, int socklen, void *arg) {
    std::cout << "client connected fd : " << fd << std::endl;
    event_base *base = (event_base *) arg;

    //下面代码是为这个fd创建一个bufferevent
    bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, read_cb, NULL, error_cb, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}


void read_cb(bufferevent *bev, void *arg) {
    char msg[5];
    std::cout << "evbuffer length : " << evbuffer_get_length(bufferevent_get_input(bev)) << std::endl;
    int len = bufferevent_read(bev, msg, sizeof(msg));
    std::cout << "read the data : " << msg << std::endl;

    std::string reply("reply");
    bufferevent_write(bev, reply.data(), reply.length());
    std::cout << "reply : " << reply << std::endl;
}

void error_cb(bufferevent *bev, short events, void *arg) {
    if (events & BEV_EVENT_CONNECTED) {
        std::cout << "client conneted." << std::endl;
        return;
    } else if (events & BEV_EVENT_EOF) {
        std::cout << "connection closed" << std::endl;
    } else if (events & BEV_EVENT_ERROR) {
        std::cout << "some other error" << std::endl;
    }
    // 这将自动 close 套接字和 free 读写缓冲区
    bufferevent_free(bev);
}
