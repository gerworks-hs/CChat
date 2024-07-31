#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
	if (argc != 2) { //Check correct app usage
		fprintf(stderr, "Usage is -> %s <port>", argv[0]);
		return 1;
	}
	long localPort = strtol(argv[1], NULL, 10); //Convert port in argv to long using strtol
	if (localPort < 1 || localPort > 65535) {
		fprintf(stderr, "The port is invalid or out of range\n");
		return 1;
	}
	fprintf(stdout, "Server will listen on port %lu\n", localPort);
	const int clientSock_fd = socket(AF_INET, SOCK_STREAM, 0); //Create client socket and check for errors
	if (clientSock_fd == -1) {
		fprintf(stderr, "Failed to create client socket, aborting...\n");
		return 1;
	}
	fprintf(stdout, "Client local socket created\n");
	struct sockaddr_in server_address; //Define server address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(localPort);
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
	
	if (connect(clientSock_fd, (const struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
		fprintf(stderr, "Error when trying to connect to the server, aborting...\n");
		close(clientSock_fd);
		return 1;
	}
	fprintf(stdout, "Connected to local server on port <%s>\n", argv[1]);
	char hellomsg[6] = "Hello";
	int bytesSent = send(clientSock_fd, &hellomsg, 5, 0);
	if (bytesSent == -1) {
		fprintf(stderr, "Error sending message to the server, aborting...\n");
		close(clientSock_fd);
		return 1;
	}
	fprintf(stdout, "Message sent to the server -> %s\n", hellomsg);
	fprintf(stdout, "Bytes sent -> %d\n", bytesSent);
	close(clientSock_fd);
	return 0;
}
