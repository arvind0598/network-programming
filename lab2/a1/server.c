#include "../server.h"

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server = sa_server_default();

	int sockfd = socket_s(AF_INET, SOCK_STREAM, 0);
	bind_s(sockfd, (SA*)&server, sizeof(server));
	listen_s(sockfd, 1);

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

	while(1) {
		server_read_str(clientfd, sockfd, buffer);
        if(!strcmp(buffer, "stop")) break;

        struct lab2_qa1 obj;
        int file_status = file_exists(buffer);

        if(file_status) {
            obj.length = get_filesize(buffer);
            get_additional_filedata(buffer, obj.data);
        }
        else {
            obj.length = -1;
        }
        server_write(clientfd, sockfd, (const void*)&obj, sizeof(obj));
	}

	close(clientfd);
	close(sockfd);
	return 0;
}	