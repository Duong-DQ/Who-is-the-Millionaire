#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BACKLOG 2   /* Number of allowed connections */
#define BUFF_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PortNumber>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);

    // Step 1: Construct a TCP socket to listen connection request
    int listen_sock;
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Step 2: setsockopt(SO_REUSEADDR) and bind address to socket
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listen_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Step 3: Listen request from client
    if (listen(listen_sock, BACKLOG) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Step 4: Accept new connect
    int conn_sock;
    struct sockaddr_in client;
    int sin_size = sizeof(struct sockaddr_in);

    if ((conn_sock = accept(listen_sock, (struct sockaddr*)&client, &sin_size)) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("You got a connection from %s\n", inet_ntoa(client.sin_addr));


    /*
    //Step 4: Communicate with client
    char buff[BUFF_SIZE];
    int bytes_sent = send(conn_sock, buff, strlen(buff), 0);
    if (bytes_sent < 0) {
        printf("\nConnection closed");
        exit(EXIT_FAILURE);
    }
    int bytes_received = recv(conn_sock, buff, BUFF_SIZE - 1, 0);
    if (bytes_received <= 1) {
        printf("\nConnection closed");
        exit(EXIT_FAILURE);
    }
    close(conn_sock);
    */

    close(listen_sock);
    return 0;
}