#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
	const int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(33);
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

	connect(client_socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));
	
	fprintf(stdout, "Connection stablished\n");

	char buffer[13];	

	recv(client_socket_fd, &buffer, sizeof(buffer), 0);

	fprintf(stdout, "Message received -> %s\n", buffer);

	close(client_socket_fd);
	return 0;
}
