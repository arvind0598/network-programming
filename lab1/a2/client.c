#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE] = {"sample message."};

	int sockfd = socket_udp_default();
	SA_IN server = sa_client_default();
	int server_len = sizeof(server);

	udp_send(sockfd, buffer, sizeof(buffer), 0, (SA*)&server, sizeof(server));

	close(sockfd);
	return 0;
}