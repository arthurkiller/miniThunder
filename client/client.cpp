#include "client.h"
#define EPOLL_SIZE 10
#define BUFFER_SIZE 8192

int epoll_fd;
char* buf;

int init() {
    epoll_fd = epoll_create(EPOLL_SIZE);
    buf = (char*)malloc(BUFFER_SIZE);
    return 0;
}

int connect_server(std::string server, int port){
    auto socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    int errno;

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    if(inet_pton(AF_INET,server,&servaddr.sin_addr) <= 0){
        perror("inet error:");
        goto err_close;
    }
    //connect to server
    connect(socketfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    //add to epoll event list
    add_event(epoll_fd,socketfd,EPOLLIN);

    while(1) {
        int n = epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
        if(n < 0){
            fprintf(stderr,"epoll wait event error\n");
            goto err_close;
        }
        // TODO associate:
        // if success, then open the file
        int file_fd; 

        errno = handle_event(file_fd, events, n);
        if (errno < 0) {
            fprintf(stderr,"event handle error\n");
            goto err_close;
        }

        // test if the epoll is null? then exit???
    }
    close(epoll_fd);
    return 0;
err_close:
    return -1;
}


int handle_event(int file_fd,struct epoll_event *events, int num){
    // get the fired fd
    for (int i = 0 ; i < num; i++) {
        if(!(events[i].events & EPOLLIN)){
            // error
            return -1;
        }
        // copy all into the file_fd
        int errn = copy_all(events[i].data.fd,file_fd);
        if (errn < 0) {
            return -1;
        }
    }
    return 0;
}


int copy_all(int src, int dst) {
    int total, nread, errn;
    while(1) {
    // read from src into buffer till EOF or EAGAIN
         nread = read(src,buf,BUFFER_SIZE);
         if (nread < 0) {
         }
         if (nread == 0) {
             // done and return
         }
         if (nread == EAGAIN) {
             // wait for next time read
         }

         errn = write(dst,buf,nread);
         if (errn < 0) {
         }
    // write into dst till error
    }

    // return all the write butes numbers
    return total;
}

int main(int argc, char **argv) {

    // do the init:
    //      handle the arguments get server & port
    //      create EPOLL
    // connect to server
    // handle the epoll watit loop
    // handle every event
    // if epoll list is null, exit

    return 0;
};
