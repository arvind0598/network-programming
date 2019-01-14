#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket_udp_default();
	SA_IN server = sa_server_default();
	bind_s(sockfd, (const SA*)&server, sizeof(server));

	SA_IN client;
	int client_len = sizeof(client);

	udp_recv(sockfd, buffer, sizeof(buffer), 0, (SA*)&client, &client_len);

	int client_sin_port = ntohs(client.sin_port);
	char client_sin_addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, (const void*)&server.sin_addr, client_sin_addr, sizeof(client_sin_addr));

	printf("%s:%d has pinged the server.\n", client_sin_addr, client_sin_port);

	close(sockfd);
	return 0;
}