#include <stdio.h>
#include <sys/socket.h>
#define PORT 2135

int main(int argc, char** argv) {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //Socket FD
	
	int local_address;
	inet_pton(AF_INET, "127.0.0.1", local_address);	

	struct sockaddr_in server_address { //Endpoint (server)
		AF_INET,
		htons(PORT),
		local_address	
	}
 
	bind(socket_fd, server_address, sizeof(server_address));	

	close(socket_fd);	

	return 0;	
}
