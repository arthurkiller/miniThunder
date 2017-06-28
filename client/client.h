#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>

// connect_server request to connect server with give address, return socket fd
int connect_server(std::string server);

// handle_event handle the epoll event return a positive int for success
// copy the data into the fd until EAGAIN
// TODO add a buffer poll for reuse buffer
int handle_event(int file_fd,struct epoll_event *events);

// copy_all will read the src and write to the dest until read the EAGAIN or read the EOF
int copy_all(int src, int dst);
