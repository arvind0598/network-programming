#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket_udp_default();
	SA_IN server = sa_client_default();
	int server_len = sizeof(server);

	while(1) {
		printf("Enter a word to check for palindrome.\n");
		scanf("%s", buffer);
		udp_send(sockfd, buffer, sizeof(buffer), 0, (SA*)&server, sizeof(server));
		
		if(!strcmp(buffer, "halt")) break;
		
		struct lab1_q2 obj;
		udp_recv(sockfd, (void*) &obj, sizeof(obj), 0, (SA*)&server, &server_len);
		if(obj.status == -1) {
			printf("The string is not a palindrome.\n");
		}
		else {
			printf("The string is a palindrome of length %d\n. Vowel frequency:\n", obj.status);
			SHOW(obj.vowels, 5);
		}
	}

	close(sockfd);
	return 0;
}