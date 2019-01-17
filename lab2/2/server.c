#include "../server.h"

int main()
{
	char buffer[BUFF_SIZE];
	SA_IN server = sa_server_default();
	int status = 0;

	int sockfd = socket_udp_default();
	bind_s(sockfd, (const SA *)&server, sizeof(server));

	SA_IN client;
	int client_len = sizeof(client);

	udp_recv(sockfd, (void *)&buffer, sizeof(buffer), 0, (SA *)&client, &client_len);
	char filename[BUFF_SIZE];
	strcpy(filename, buffer);
	status = file_exists(filename);
	udp_send(sockfd, (void *)&status, sizeof(status), 0, (const SA *)&client, client_len);

	int exit = 0;
	while (1)
	{
		int option;
		udp_recv(sockfd, (void *)&option, sizeof(option), 0, (SA *)&client, &client_len);
		switch (option)
		{
		// search
		case 1:
		{
			udp_recv(sockfd, (void *)&buffer, sizeof(buffer), 0, (SA *)&client, &client_len);
			status = search_in_file(filename, buffer);
			udp_send(sockfd, (void *)&status, sizeof(status), 0, (const SA *)&client, client_len);
			break;
		}
		// replace
		case 2:
		{
			char old_word[BUFF_SIZE];
			udp_recv(sockfd, (void *)&old_word, sizeof(old_word), 0, (SA *)&client, &client_len);
			char new_word[BUFF_SIZE];
			udp_recv(sockfd, (void *)&new_word, sizeof(new_word), 0, (SA *)&client, &client_len);
			status = replace_in_file(filename, old_word, new_word);
			udp_send(sockfd, (void *)&status, sizeof(status), 0, (const SA *)&client, client_len);
			break;
		}
		// reorder
		case 3:
		{
			status = sort_file_ascii(filename);
			udp_send(sockfd, (void *)&status, sizeof(status), 0, (const SA *)&client, client_len);
			break;
		}
		// exit
		default:
			exit = 1;
		}
		if (exit)
			break;
	}
	close(sockfd);
	return 0;
}
