#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server = sa_server_default();

	int sockfd = socket_tcp_default();
	bind_s(sockfd, (SA*)&server, sizeof(server));
	listen_s(sockfd, 1);

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

	int client_sin_port = ntohs(client.sin_port);
	char client_sin_addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, (const void*)&server.sin_addr, client_sin_addr, sizeof(client_sin_addr));

	printf("%s:%d connected as %d.\n", client_sin_addr, client_sin_port, clientfd);
	close(clientfd);
	close(sockfd);
	return 0;
}
