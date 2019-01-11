#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket_s(AF_INET, SOCK_DGRAM, 0);
	SA_IN server = sa_client_default();
	int server_len = sizeof(server);

	while(1) {
		printf("Enter a word to check for palindrome.\n");
		scanf("%s", buffer);
		udp_send(sockfd, buffer, sizeof(buffer), 0, (SA*)&server, sizeof(server));
		
		if(!strcmp(buffer, "stop")) break;
		udp_recv(sockfd, buffer, sizeof(buffer), 0, (SA*)&server, &server_len);
		printf("%s\n", buffer);
	}

	close(sockfd);
	return 0;
}