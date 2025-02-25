#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[256];

    // Create a TCP socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Send and receive messages
    while (1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(sock_fd, buffer, strlen(buffer));

        memset(buffer, 0, sizeof(buffer));
        int len = read(sock_fd, buffer, sizeof(buffer));
        if (len == 0) break;
        printf("Server: %s\n", buffer);
    }

    close(sock_fd);
    return 0;
}
