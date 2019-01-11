#include "../../lab.h"

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server= sa_client_default();

	int sockfd = socket_s(AF_INET, SOCK_STREAM, 0);
	connect_s(sockfd, (SA*)&server, sizeof(server));

	printf("Enter size of array.\n");
	int arr_size = client_get_write_int(sockfd);

	printf("Enter %d integers.\n", arr_size);
	int *arr = stdin_get_intarr(arr_size);
	client_write_intarr(sockfd, arr, arr_size);

	int exit = 0;

	while(1) {
		printf("Search(1), Sort(2) or Split(3)? Anything else will exit.\n");
		int choice = client_get_write_int(sockfd);

		switch(choice) {

			case 1: {
				printf("Enter element to search for.\n");
				int key = client_get_write_int(sockfd);
				int pos = client_read_int(sockfd);
				if(pos == -1) printf("Element not found.\n");
				else printf("Element at position %d.\n", pos);
				break;
			}

			case 2:
			case 3: {
				int *res = client_read_intarr(sockfd, arr_size);
				SHOW(res, arr_size);
				break;
			}

			default: {
				printf("Exiting.\n");
				client_write_int(sockfd, 4);
				exit = 1;
			}
		}

		if(exit) break;
	}

	close(sockfd);
	return 0;
}