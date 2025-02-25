 Simple Chat Application Using Unix and Internet Domain Sockets
This project demonstrates a simple chat application using two types of socket communication: Unix Domain Sockets (for local communication on the same machine) and Internet Domain Sockets (for communication over a network or the internet). The application consists of two programs, a server and a client, which exchange text messages.

In the Unix Domain Sockets version, the server listens on a local file (e.g., /tmp/chat_socket), and the client connects to it. This method is faster and more secure for local communication as it doesn’t involve network protocols.

In the Internet Domain Sockets version, the server listens on a specific IP address and port number. The client connects to the server using the server’s IP and port. This allows communication between programs on different machines over a network or the internet.

The client sends messages to the server, which processes the message and responds. The client then receives and displays the server's response in real-time. The user can continue sending and receiving messages until they decide to exit.

This project introduces basic socket programming concepts and can be extended for features like multiple client support, graphical interfaces, encryption, or file sharing.
