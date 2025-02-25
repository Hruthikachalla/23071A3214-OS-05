#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CONNECTIONS 5

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[256];

    // Create a TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    // Bind the socket to an address
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept a client connection
    if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Receive and send messages
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int len = read(client_fd, buffer, sizeof(buffer));
        if (len == 0) break;
        printf("Client: %s\n", buffer);

        // Send a response back
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(client_fd, buffer, strlen(buffer));
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
