#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server= sa_client_default();
    int status = 0;

	int sockfd = socket_s(AF_INET, SOCK_STREAM, 0);
	connect_s(sockfd, (SA*)&server, sizeof(server));

	while(1) {
        printf("Enter file name.\n");
        stdin_get_str(buffer);
        client_write_str(sockfd, buffer);

        if(!strcmp(buffer, "stop")) break;

        struct lab2_qa1 obj;
        client_read(sockfd, (void*)&obj, sizeof(obj));

        if(obj.length == -1) {
            printf("The file does not exist.\n");
        }
        else {
            printf("The file is %d bytes long.\n", obj.length);
            SHOW(obj.data, 5);
        }
    }
	close(sockfd);
	return 0;
}