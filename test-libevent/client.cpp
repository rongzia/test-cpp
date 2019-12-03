#include <cstring>
#include <iostream>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

void write_fun(int fd, short events, void *arg) {
    bufferevent *bev = (bufferevent *) arg;

    std::string msg("hello");
    int len = bufferevent_write(bev, msg.data(), msg.length());
//    ssize_t len = write(bufferevent_getfd(bev), msg.data(), msg.length());        // 同上，都是写入
//    std::cout << "client write the data : " << msg << std::endl;
}

void read_cb(bufferevent *bev, void *arg) {
    char buf[5];
    size_t len = bufferevent_read(bev, buf, sizeof(buf));
    std::string reply(buf, 5);
    std::cout << "reply : " << buf << std::endl;
}

void error_cb(bufferevent *bev, short events, void *arg) {
    std::cout << "error_cb :";
    if (events & BEV_EVENT_EOF) {
        std::cout << "connection closed" << std::endl;
    } else if (events & BEV_EVENT_ERROR) {
        std::cout << "some other error" << std::endl;
    } else if (events & BEV_EVENT_CONNECTED) {
        std::cout << "connected" << std::endl;
        return;
    }

    bufferevent_free(bev);
}

bufferevent *connect_new(event_base *ev_base, int port) {
    struct sockaddr_in addr;;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct bufferevent *bev = bufferevent_socket_new(ev_base, -1, BEV_OPT_CLOSE_ON_FREE);

    std::cout << "before bufferevent_socket_connect, bufferevent_getfd() : " << bufferevent_getfd(bev) << std::endl;
    if (bufferevent_socket_connect(bev, (struct sockaddr *) &addr, sizeof(addr)) < 0) {}
    std::cout << "connected fd == bufferevent_getfd() : " << bufferevent_getfd(bev) << std::endl;

    bufferevent_setcb(bev, read_cb, NULL, NULL, ev_base);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    return bev;
}

int main() {

    struct event_base *ev_base = event_base_new();

    bufferevent *bev = connect_new(ev_base, 8989);



    std::string msg("hello");
    int len;
    bufferevent_write(bev, msg.data(), msg.length());
    bufferevent_write(bev, msg.data(), msg.length());
    bufferevent_write(bev, msg.data(), msg.length());
    write(bufferevent_getfd(bev), msg.data(), msg.length());        // 同上，都是写入
    write(bufferevent_getfd(bev), msg.data(), msg.length());        // 同上，都是写入
    write(bufferevent_getfd(bev), msg.data(), msg.length());        // 同上，都是写入
    write(bufferevent_getfd(bev), msg.data(), msg.length());        // 同上，都是写入

//    event_base_loop(ev_base, EVLOOP_NONBLOCK);
    event_base_dispatch(ev_base);



    event_base_free(ev_base);


    return 0;
}