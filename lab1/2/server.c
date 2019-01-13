#include "../../lab.h"

int is_palindrome(char *a) {
	int n = strlen(a);
	for(int i = 0; i <= n/2; i++) {
		if(a[i] != a[n - i - 1])
			return 0;
	}
	return 1;
}

void count_vowels(int *x, char *a) {
	for(int i = 0; i < 5; i++) x[i] = 0;

	int n = strlen(a);
	for(int i = 0; i < n; i++) {
		if(a[i] == 'a' || a[i] == 'A') x[0]++;
		else if(a[i] == 'e' || a[i] == 'E') x[1]++;
		else if(a[i] == 'i' || a[i] == 'I') x[2]++;
		else if(a[i] == 'o' || a[i] == 'O') x[3]++;
		else if(a[i] == 'u' || a[i] == 'U') x[4]++;
	}
}

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket_s(AF_INET, SOCK_DGRAM, 0);
	SA_IN server = sa_server_default();
	bind_s(sockfd, (const SA*)&server, sizeof(server));

	SA_IN client;
	int client_len = sizeof(client);

	while(1) {
		udp_recv(sockfd, buffer, sizeof(buffer), 0, (SA*)&client, &client_len);
		if(!strcmp(buffer, "halt")) break;
		
		struct lab1_q2 obj;
		if(is_palindrome(buffer)) {
			obj.status = strlen(buffer);
			count_vowels(obj.vowels, buffer);
		}
		else obj.status = -1;

		udp_send(sockfd, (const void*)&obj, sizeof(obj), 0, (SA*)&client, sizeof(client));
	}

	close(sockfd);
	return 0;
}