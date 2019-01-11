#include "../../lab.h"

int is_palindrome(char *a) {
	int n = strlen(a);
	for(int i = 0; i <= n/2; i++) {
		if(a[i] != a[n - i - 1])
			return 0;
	}
	return 1;
}

int main() {
	char buffer[BUFF_SIZE];
	char SUCCESS_MESSAGE[] = {"The string is a palindrome."};
	char FAILURE_MESSAGE[] = {"The string is NOT a palindrome."};

	int sockfd = socket_s(AF_INET, SOCK_DGRAM, 0);
	SA_IN server = sa_server_default();
	bind_s(sockfd, (const SA*)&server, sizeof(server));

	SA_IN client;
	int client_len = sizeof(client);

	while(1) {
		udp_recv(sockfd, buffer, sizeof(buffer), 0, (SA*)&client, &client_len);
		if(!strcmp(buffer, "stop")) break;
		
		if(is_palindrome(buffer)) strcpy(buffer, SUCCESS_MESSAGE);
		else strcpy(buffer, FAILURE_MESSAGE);
		udp_send(sockfd, buffer, sizeof(buffer), 0, (SA*)&client, sizeof(client));
	}

	close(sockfd);
	return 0;
}