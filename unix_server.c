#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/chat_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[256];

    // Create a Unix domain socket
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s\n", SOCKET_PATH);

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
    unlink(SOCKET_PATH);
    return 0;
}
