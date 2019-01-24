#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket_udp_default();
	SA_IN server = sa_client_default();
	int server_len = sizeof(server);

	printf("Enter file name.\n");
	stdin_get_str(buffer);
	udp_send(sockfd, buffer, sizeof(buffer), 0, (SA *)&server, server_len);

	int status;
	udp_recv(sockfd, (void *)&status, sizeof(status), 0, (SA *)&server, &server_len);
	printf("%s\n", status ? "File exists. Continue." : "File does not exist.");
	if (!status) error_c(sockfd);

	int exit = 0;
	while (1) {
		int option;
		scanf("%d", &option);
		udp_send(sockfd, (void *)&option, sizeof(option), 0, (const SA *)&server, server_len);

		switch (option) {
			// search
			case 1: {
				printf("Enter word to search for.\n");
				stdin_get_str(buffer);
				udp_send(sockfd, buffer, sizeof(buffer), 0, (SA *)&server, server_len);
				udp_recv(sockfd, (void *)&status, sizeof(status), 0, (SA *)&server, &server_len);
				if (status == -1)
					printf("There was an error.\n");
				else
					printf("The word occured %d times.\n", status);
				break;
			}
			// replace
			case 2: {
				printf("Enter old word.\n");
				stdin_get_str(buffer);
				udp_send(sockfd, buffer, sizeof(buffer), 0, (SA *)&server, server_len);
				printf("Enter new word.\n");
				stdin_get_str(buffer);
				udp_send(sockfd, buffer, sizeof(buffer), 0, (SA *)&server, server_len);
				udp_recv(sockfd, (void *)&status, sizeof(status), 0, (SA *)&server, &server_len);
				printf("%s\n", status ? "String replaced." : "String was not found.");
				break;
			}
			// reorder
			case 3: {
				udp_recv(sockfd, (void *)&status, sizeof(status), 0, (SA *)&server, &server_len);
				printf("The file was sorted.\n");
				break;
			}
			// exit
			default: {
				printf("Exiting.\n");
				exit = 1;
			}
		}
		if (exit) break;
		printf("Enter next option.\n");
	}

	close(sockfd);
	return 0;
}