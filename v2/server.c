#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
	//Check for correct app usage
	if (argc != 2) {
		fprintf(stderr, "Usage is -> %s <port>\n", argv[0]);
		return 1;
	}
	//Convert port saved in a char pointer to a long, checking later overflows and underflows
	long localPort = strtol(argv[1], NULL, 10); //Base 10 is used to convert in 0-9 range, end of conversion is nulled
	if (localPort < 1 || localPort > 65535) { //Check if the port is in range, if it is not, abort
		fprintf(stderr, "The port is invalid or out of range, aborting...\n");
		return 1;
	}
	fprintf(stdout, "Server will listen on port %lu\n", localPort);

	//Finished argument checks, here starts the sockets code
	//Server socket creation
	const int servSock_fd = socket(AF_INET, SOCK_STREAM, 0);	
	if (servSock_fd == -1) { //Check for succesful creation
		fprintf(stderr, "Error creating the server socket, aborting...\n");
		return 1;
	}
	fprintf(stdout, "Server socket created succesfully\n");
	//Define server address structure, later it will be bind to the server socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(localPort); //Convert port into network byte order
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr); //Convert loopback address into network byte order
	//Bind server address structure to server socket
	if ((bind(servSock_fd, (const struct sockaddr *)&server_address, sizeof(server_address))) != 0) { //Check for succesful binding
		fprintf(stderr, "Failed binding server address to local socket, aborting...\n");
		close(servSock_fd);
		return 1;
	}
	fprintf(stdout, "Server address succesfully bound to local socket\n");
	//Listen for incoming conections from clients
	//Set server local socket as listening with a max of 5 connections in queue and check for succesful completion
	if ((listen(servSock_fd, 5)) != 0) {
		fprintf(stderr, "Failed to set socket state as <listening>\n");
		close(servSock_fd);
		return 1;
	}
	fprintf(stdout, "Server local socket is now listening for incoming connections\n");
	//Start connection handler (loop)
	while (1) {
		int inc_fd = accept(servSock_fd, NULL, NULL); //Accept the next incoming connection to the socket, null to throw incoming address
		if (inc_fd == -1) { //If accept() returns -1, there are no more connections to handle, server local socket is closed
			fprintf(stdout, "No more incoming connections to accept\n");
			close(servSock_fd);
			return 0;
		}
		char *buffer = malloc(sizeof(char) * 6); //Allocate buffer for message "Hello" (null-terminated)
		int bytesRec = recv(inc_fd, buffer, (sizeof(char) * 6), 0); //Call recv() and save its return value into bytesRec
		if (bytesRec == -1) { //If bytesRec equals -1 an error ocurred, abort
			fprintf(stderr, "Error trying to read from current connection socket\n");
			free(buffer);
			close(inc_fd);
			close(servSock_fd);
			return 1;
		} else if (bytesRec == 0) { //If bytesRec equals 0 the connection was gracefully closed
			fprintf(stdout, "Connection has been closed by the client gracefully, no more data will be sent\n");
			free(buffer);
			close(inc_fd);
			close(servSock_fd);
			return 0;
		} //Else, on a positive integer
		fprintf(stdout, "Bytes read from current connection socket: %d", bytesRec);
		fprintf(stdout, "Message from client: %s", buffer);
		free(buffer);
		close(inc_fd);
		close(servSock_fd);
		break;
	}
	return 0;
}
