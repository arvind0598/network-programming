#include "../../lab.h"

int search_arr(int *arr, int x, int n) {
	int pos = -1;
	for(int i = 0; i < n; i++) {
		if(arr[i] == x) return i;
	}
	return pos;
}

int *sort_arr(int *arr, int n) {
	int *a = malloc(n * sizeof(int));
	memcpy(a, arr, n * sizeof(int));
	qsort(a, n, sizeof(int), compare_int);
	return a;
}

int *oddeven_arr(int *arr, int n) {
	int *a = malloc(n * sizeof(int));
	memcpy(a, arr, n * sizeof(int));
	int j = -1;
	for(int i = 0; i < n; i++)
		if(a[i] % 2 == 0) {
			j += 1;
			SWAP(a[i], a[j]);
		}
	return a;
}

int main() {
	char buffer[BUFF_SIZE];
	SA_IN server = sa_server_default();

	int sockfd = socket_tcp_default();
	bind_s(sockfd, (SA*)&server, sizeof(server));
	listen_s(sockfd, 1);

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

	int arr_size = server_read_int(clientfd, sockfd);
	int *arr = server_read_intarr(clientfd, sockfd, arr_size);

	int exit = 0;

	while(1) {
		int choice = server_read_int(clientfd, sockfd);
		switch(choice) {
		
			// search in array
			case 1: {
				int key = server_read_int(clientfd, sockfd);
				server_write_int(clientfd, sockfd, search_arr(arr, key, arr_size));
				break;
			}

			// sort array
			case 2: {
				int *sorted_arr = sort_arr(arr, arr_size);
				server_write_intarr(clientfd, sockfd, sorted_arr, arr_size);
				break;
			}

			// split into even and odd
			case 3: {
				int *split_arr = oddeven_arr(arr, arr_size);
				server_write_intarr(clientfd, sockfd, split_arr, arr_size);
				break;
			}

			default: {
				printf("Exiting.\n");
				exit = 1;	
			}
		}

		if(exit) break;
	}

	close(clientfd);
	close(sockfd);
	return 0;
}

