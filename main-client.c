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

int main(void) {
    struct addrinfo hints = {0}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo("localhost", "50000", &hints, &res) == -1) {
        perror("getaddrinfo");
        exit(1);
    }
    int socketfd;
    if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socketfd");
        exit(1);
    }
    if (connect(socketfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("connect");
        exit(1);
    }
    char *msg = "Hello World!\0";
    if (send(socketfd, msg, strlen(msg), 0) == -1) {
        perror("send");
        exit(1);
    }
    printf("Sent : %s",msg);
    return 0;
}
