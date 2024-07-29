#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {

	const int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); //Creating the server socket file descriptor and saving it into socket_fd
	const struct in_addr *loopback_addr = malloc(4); //Allocate 4 bytes (32bit) pointer to save the in_addr struct in network byte order
	
	inet_pton(AF_INET, "127.0.0.1", loopback_addr); //Convert loopback address to network byte order and send it to loopback_addr

	const struct sockaddr_in server_address {
		AF_INET
		htons(33); //Convert port into network byte order
		*loopback_addr //Retrieve the in_addr struct saved in this pointer
	}

	bind(server_socket_fd, &server_address, sizeof(server_address));

	listen(server_socket_fd, 1);

	return 0;	
}
