#include "../../lab.h"

int main()
{
	char buffer[BUFF_SIZE];
	SA_IN server = sa_client_default();
	int status = 0;

	int sockfd = socket_tcp_default();
	connect_s(sockfd, (SA *)&server, sizeof(server));

	printf("Enter file name.\n");
	stdin_get_str(buffer);
	client_write_str(sockfd, buffer);

	status = client_read_int(sockfd);
	printf("%s\n", status ? "File exists. Continue." : "File does not exist.");
	if (!status)
		error_c(sockfd);

	printf("1. Search\n2. Replace\n3. Reorder\n4. Exit\n");
	int exit = 0;
	while (1)
	{
		int option = client_get_write_int(sockfd);
		switch (option)
		{
		// search
		case 1:
		{
			printf("Enter word to search for.\n");
			stdin_get_str(buffer);
			client_write_str(sockfd, buffer);
			status = client_read_int(sockfd);
			if (status == -1)
				printf("There was an error.\n");
			else
				printf("The word occured %d times.\n", status);
			break;
		}
		// replace
		case 2:
		{
			printf("Enter old word.\n");
			stdin_get_str(buffer);
			client_write_str(sockfd, buffer);
			printf("Enter new word.\n");
			stdin_get_str(buffer);
			client_write_str(sockfd, buffer);
			status = client_read_int(sockfd);
			printf("%s\n", status ? "String replaced." : "String was not found.");
			break;
		}
		// reorder
		case 3:
		{
			status = client_read_int(sockfd);
			printf("The file was sorted.\n");
			break;
		}
		// exit
		default:
		{
			printf("Exiting.\n");
			exit = 1;
		}
		}
		if (exit)
			break;
		printf("Enter next option.\n");
	}

	close(sockfd);
	return 0;
}