#include "../server.h"

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server = sa_server_default();
	int status = 0;

	int sockfd = socket_s(AF_INET, SOCK_STREAM, 0);
	bind_s(sockfd, (SA*)&server, sizeof(server));
	listen_s(sockfd, 1);

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept_s(sockfd, (SA*)&client, &client_len);
	
	server_read_str(clientfd, sockfd, buffer);
	char filename[BUFF_SIZE];
	strcpy(filename, buffer);
	status = file_exists(filename);
	server_write_int(clientfd, sockfd, status);

	int exit = 0;
	while(1) {
		int option = server_read_int(clientfd, sockfd);
		switch(option) {
			// search
			case 1: {
				server_read_str(clientfd, sockfd, buffer);
				status = search_in_file(filename, buffer);
				server_write_int(clientfd, sockfd, status);
				break;
			}
			// replace
			case 2: {
                char old_word[BUFF_SIZE];
                server_read_str(clientfd, sockfd, old_word);
                char new_word[BUFF_SIZE];
                server_read_str(clientfd, sockfd, new_word);
                status = replace_in_file(filename, old_word, new_word);
                server_write_int(clientfd, sockfd, status);
                break;
            }
			// reorder
			case 3: {
                status = sort_file_ascii(filename);
                server_write_int(clientfd, sockfd, status);
                break;
            }
			// exit
			default: exit = 1;
		}
		if(exit) break;
	}

	close(clientfd);
	close(sockfd);
	return 0;
}	