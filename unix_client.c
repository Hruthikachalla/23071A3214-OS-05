#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/chat_socket"

int main() {
    int sock_fd;
    struct sockaddr_un addr;
    char buffer[256];

    // Create a Unix domain socket
    if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Connect to the server
    if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
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
