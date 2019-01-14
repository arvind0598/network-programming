#include "../../lab.h"

int main() {
	SA_IN server= sa_client_default();
	int sockfd = socket_tcp_default();
	connect_s(sockfd, (SA*)&server, sizeof(server));
	close(sockfd);
	return 0;
}