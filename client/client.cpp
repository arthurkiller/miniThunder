#include"client.h"

int epoll_fd;

static int connect_server(std::string server, int port){
    auto socketfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    if(inet_pton(AF_INET,server,&servaddr.sin_addr) <= 0){
        perror("inet error:");
    }
    //connect to server
    connect(socketfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    //add to epoll event list
    add_event(epoll_fd,socketfd,EPOLLIN);

    return 0;
};


static int handle_event(int file_fd,struct epoll_event *events){
    // get the fired fd
    // copy all into the file_fd

    return 0;
};


static int copy_all(int src, int dst) {
    // make a buffer
    // read from src into buffer till EOF or EAGAIN
    // write into dst till error
    // return all the write butes numbers

    return 0;
}

int main(int argc, char **argv) {

    // do the init:
    //      handle the arguments get server & port
    //      create EPOLL
    //      do the protocol associate (TODO)
    // connect to server
    // handle the epoll watit loop
    // handle every event
    // if epoll list is null, exit

    return 0;
};
