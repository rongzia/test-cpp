#include <cstring>
#include <iostream>
#include <unistd.h>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

void write_fun(int socket_fd, short events, void *arg) {
    bufferevent *bev = (bufferevent *) arg;
    std::cout << "connect id : " << bufferevent_getfd(bev) << std::endl;

    for (int i = 0; i < 10; i++) {
        std::string msg(std::to_string(i));
        bufferevent_write(bev, msg.data(), msg.length());
        std::cout << msg << std::endl;
    }
}

void read_cb(bufferevent *bev, void *arg) {
    char buf[5];
    size_t len = bufferevent_read(bev, buf, sizeof(buf));
    std::string reply(buf, 5);
    std::cout << "reply : " << buf << std::endl;
}

void error_cb(bufferevent *bev, short events, void *arg) {
    std::cout << "error_cb : ";
    if (events & BEV_EVENT_CONNECTED) {
        std::cout << "connect to server" << std::endl;
        return;
    } else if (events & BEV_EVENT_EOF) {
        std::cout << "connection closed" << std::endl;
    } else if (events & BEV_EVENT_ERROR) {
        std::cout << "some other error" << std::endl;
    }

    bufferevent_free(bev);
}

bufferevent *connect_new(event_base *ev_base, int port) {
    sockaddr_in addr;;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bufferevent *bev = bufferevent_socket_new(ev_base, -1, BEV_OPT_CLOSE_ON_FREE); // | BEV_OPT_THREADSAFE);

//    std::cout << "before bufferevent_socket_connect(), bufferevent_getfd() : " << bufferevent_getfd(bev) << std::endl;
    if (bufferevent_socket_connect(bev, (sockaddr *) &addr, sizeof(addr)) < 0) {}
//    std::cout << " after bufferevent_socket_connect(), bufferevent_getfd() : " << bufferevent_getfd(bev) << std::endl;

    bufferevent_setcb(bev, read_cb, NULL, error_cb, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    return bev;
}

int main() {
    event_base *base = event_base_new();
    bufferevent *bev = connect_new(base, 8989);
    std::cout << "connect id : " << bufferevent_getfd(bev) << std::endl;

    event *write_event = event_new(base, -1, EV_READ | EV_PERSIST, write_fun, bev);
    event_add(write_event, NULL);

    event_base_dispatch(base);
    event_base_free(base);
    return 0;
}

//    std::thread ev_base_thread(
//            [ev_base]() -> void { event_base_loop(ev_base, EVLOOP_NO_EXIT_ON_EMPTY); }
//    );
//    ev_base_thread.detach();