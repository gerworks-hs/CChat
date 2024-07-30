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
	if (bind(servSock_fd, &server_address, sizeof(server_address)) != 0) { //Check for succesful binding
		fprintf(stderr, "Failed binding server address to local socket, aborting...\n");
		return 1;
	}
	fprintf(stdout, "Server address succesfully bound to local socket\n");
	//Listen for incoming conections from clients
	listen();

	close(servSock_fd); //Close the server socket
	return 0;
}
