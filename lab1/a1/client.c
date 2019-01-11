#include "../../lab.h"

int main() {
	SA_IN server= sa_client_default();
	int sockfd = socket_s(AF_INET, SOCK_STREAM, 0);
	connect_s(sockfd, (SA*)&server, sizeof(server));
	close(sockfd);
	return 0;
}