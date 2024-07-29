#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {

	const int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); //Saving server socket file descriptor given by socket()
	
	//Server address structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(33); //Convert port 33 into network byte order
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr); //Convert loopback address to network byte order

	bind(server_socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address)); //Binding server address structure to local socket

	fprintf(stdout, "Server endpoint socket created and binded\n");

	listen(server_socket_fd, 1); //Start listening for connections on the socket

	fprintf(stdout, "Server listening on socket\n");

	const int client_inc_socket = accept(server_socket_fd, NULL, NULL); //Accept and stablish connection with incoming client
	
	fprintf(stdout, "Connection stablished with client\n");

	send(client_inc_socket, "Hello client", sizeof("Hello client"), 0; //Send client hello to the client
	
	fprintf(stdout, "We have sent client hello to the client\n");

	close(client_inc_socket); //Close the new incoming client socket
	close(server_socket_fd); //Close the socket (via its file descriptor)
	return 0;	
}
