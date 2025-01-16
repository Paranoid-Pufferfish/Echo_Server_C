#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    struct addrinfo hints = {0}, *res;
    struct sockaddr_storage their_addr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo("localhost","50000",&hints,&res) == -1) {
        perror("getaddrinfo");
        exit(1);
    }
    int socketfd;
    if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socketfd");
        exit(1);
    }
    if (bind(socketfd,res->ai_addr,res->ai_addrlen) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(socketfd,5)== -1) {
        perror("listen");
        exit(1);
    }
    socklen_t addr_size = sizeof their_addr;
    int newfd;
    if ((newfd = accept(socketfd, (struct sockaddr *) &their_addr, &addr_size)) == -1) {
        perror("accept");
        exit(1);
    }
    char msg[50] = {0};
    recv(newfd,msg,1024,0);
    printf("Received : %s",msg);
    close(newfd);
    close(socketfd);
    return 0;
}
