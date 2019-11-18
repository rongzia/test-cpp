//
// Created by rrzhang on 2019/10/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

#define SERV_PORT 9877
#define LISTEN_BACKLOG 32
#define MAX_LINE 1024

void do_accetp(evutil_socket_t listenfd, short event, void *arg);

void read_cb(struct bufferevent *bev, void *arg);

void error_cb(struct bufferevent *bev, short event, void *arg);

void write_cb(struct bufferevent *bev, void *arg);

int main(int argc, char *argv[]) {
    evutil_socket_t listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket\n");
        return 1;
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind\n");
        return 1;
    }
    if (listen(listenfd, LISTEN_BACKLOG) < 0) {
        perror("listen\n");
        return 1;
    }

    printf("Listening...\n");

    evutil_make_listen_socket_reuseable(listenfd);
    evutil_make_socket_nonblocking(listenfd);

    struct event_base *base = event_base_new();
    if (base == NULL) {
        perror("event_base\n");
        return 1;
    }
    const char *eventMechanism = event_base_get_method(base);
    printf("Event mechanism used is %s\n", eventMechanism);

    struct event *listen_event;
    listen_event = event_new(base, listenfd, EV_READ | EV_PERSIST, do_accetp, (void *) base);
    event_add(listen_event, NULL);
    event_base_dispatch(base);

    if (close(listenfd) < 0) {
        perror("close\n");
        return 1;
    }
    printf("The End\n");
    return 0;
}

void do_accetp(evutil_socket_t listenfd, short event, void *arg) {
    struct event_base *base = (struct event_base *) arg;
    evutil_socket_t fd;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    fd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
    if (fd < 0) {
        perror("accept\n");
        return;
    }
    if (fd > FD_SETSIZE) {
        perror("fd > FD_SETSIZE");
        if (close(fd) < 0) {
            perror("close\n");
            return;
        }
        return;
    }

    printf("Accept: fd = %u\n", fd);

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_PERSIST);
}

void read_cb(struct bufferevent *bev, void *arg) {
    char line[MAX_LINE + 1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while ((n = bufferevent_read(bev, line, MAX_LINE)) > 0) {
        line[n] = '\0';
        printf("fd = %u, read line: %s", fd, line);
        bufferevent_write(bev, line, n);
    }
}

void error_cb(struct bufferevent *bev, short event, void *arg) {
    evutil_socket_t fd = bufferevent_getfd(bev);
    printf("fd = %u, ", fd);
    if (event & BEV_EVENT_TIMEOUT)
        printf("Time out.\n");  // if bufferevent_set_timeouts() is called
    else if (event & BEV_EVENT_EOF)
        printf("Connection closed.\n");
    else if (event & BEV_EVENT_ERROR)
        printf("Some other error.\n");
    bufferevent_free(bev);
}

void write_cb(struct bufferevent *bev, void *arg) {
    // leave blank
}