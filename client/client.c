#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IPAddress> <PortNumber>\n", argv[0]);
        exit(0);
    }

    char* server_ip = argv[1]; /* 127.0.0.1 */
    int server_port = atoi(argv[2]);
    
    //Step 1: Construct socket
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);

    //Step 2: Specify server address
    struct sockaddr_in server_addr; /* server's address information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    //Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }
    
    
    /*
    Step 4: Communicate with server
    char buff[BUFF_SIZE];
    int bytes_received, bytes_sent;

    bytes_received = recv(client_sock, buff, BUFF_SIZE - 1, 0);
    if (bytes_received <= 0) {
        printf("\nError!Cannot receive data from sever!\n");
        return 0;
    }
    
    bytes_sent = send(client_sock, buff, strlen(buff), 0);
    if (bytes_sent <= 0) {
        printf("\nConnection closed!\n");
        return 0;
    }
    */


    close(client_sock);
    return 0;
}