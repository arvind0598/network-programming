#include "lab.h"

void error() {
	printf("An error occured.\n");
	exit(0);
}

void error_c(int sockfd) {
	printf("An error occured. Closing socket.\n");
	close(sockfd);
	exit(0);
}

void error_c2(int sockfd, int sockfd2) {
	printf("An error occured. Closing sockets.\n");
	close(sockfd);
	close(sockfd2);
	exit(0);
}

int socket_s(int family, int type, int protocol) {
	int sockfd = socket(family, type, protocol);
	if(sockfd < 0) error();
	else printf("Socket created.\n");
	return sockfd;
}

int bind_s(int sockfd, const SA* server, int size) {
	int status = bind(sockfd, server, size);
	if(status < 0) error();
	else printf("Socket bound.\n");
	return status;
}

int listen_s(int sockfd, int backlog) {
	int status = listen(sockfd, backlog);
	if(status < 0) error_c(sockfd);
	else printf("Socket listening.\n");
	return status;
}

int connect_s(int sockfd, SA *server, int size) {
	int status = connect(sockfd, server, size);
	if(status < 0) error();
	else printf("Connected to server.\n");
	return status;
}

int accept_s(int sockfd, SA *client, socklen_t *size) {
	int clientfd = accept(sockfd, client, size);
	if(clientfd < 0) error_c(sockfd);
	else printf("Client connected.\n");
	return clientfd;
}

int client_read_int(int sockfd) {
	int x = -1;
	int status = read(sockfd, (void*)&x, sizeof(x));
	if(status < 0) error_c(sockfd);
	return x;
}

int *client_read_intarr(int sockfd, int n) {
	int *arr = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
		arr[i] = client_read_int(sockfd);
	return arr;
}

void client_write_int(int sockfd, int x) {
	int status = write(sockfd, (void*)&x, sizeof(x));
	if(status < 0) error_c(sockfd);
}

void client_write_intarr(int sockfd, int *arr, int n) {
	for(int i = 0; i < n; i++)
		client_write_int(sockfd,arr[i]);
}

int client_get_write_int(int sockfd) {
	int x = -1;
	scanf("%d", &x);
	client_write_int(sockfd, x);
	return x;
}

int server_read_int(int clientfd, int sockfd) {
	int x = -1;
	int status = read(clientfd, (void*)&x, sizeof(x));
	if(status < 0) error_c2(clientfd, sockfd);
	return x;
}

int *server_read_intarr(int clientfd, int sockfd, int n) {
	int *arr = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
		arr[i] = server_read_int(clientfd, sockfd);
	return arr;
}

void server_write_int(int clientfd, int sockfd, int x) {
	int status = write(clientfd, (void*)&x, sizeof(x));
	if(status < 0) error_c2(clientfd, sockfd);
}

void server_write_intarr(int clientfd, int sockfd, int *arr, int n) {
	for(int i = 0; i < n; i++)
		server_write_int(clientfd, sockfd,arr[i]);
}

int socket_tcp_default() {
	return socket_s(AF_INET, SOCK_STREAM, 0);
}

int socket_udp_default() {
	return socket_s(AF_INET, SOCK_DGRAM, 0);
}

int udp_send(int sockfd, const void* msg, int len, int flags, const SA* to, int tolen) {
	int status = sendto(sockfd, msg, len, flags, to, tolen);
	if(status < 0) error_c(sockfd);
	return status;
}

int udp_recv(int sockfd, void *msg, int len, int flags, SA* from, int *fromlen) {
	int status = recvfrom(sockfd, msg, len, flags, from, fromlen);
	if(status < 0) error_c(sockfd);
	return status;
}

SA_IN sa_init(int family, int port, int address) {
	SA_IN obj;
	obj.sin_family = family;
	obj.sin_port = port;
	obj.sin_addr.s_addr = address;
	return obj;
}

SA_IN sa_server_default() {
	SA_IN server = sa_init(AF_INET, htons(PORT), htonl(INADDR_ANY));
	return server;
}

SA_IN sa_client_default() {
	SA_IN server = sa_init(AF_INET, htons(PORT), inet_addr("127.0.0.1"));
	return server;
}

int *stdin_get_intarr(int n) {
	int *arr = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
	return arr;
}

/* lab 2 */

void stdin_get_str(char *buffer) {
	scanf("%s", buffer);
}

void client_read_str(int sockfd, char *buffer) {
	int status = read(sockfd, (void*)buffer, BUFF_SIZE);
	if(status < 0) error_c(sockfd);
}

void client_write_str(int sockfd, char *buffer) {
	int status = write(sockfd, (void*)buffer, BUFF_SIZE);
	if(status < 0) error_c(sockfd);
}

void server_read_str(int clientfd, int sockfd, char *buffer) {
	int status = read(clientfd, (void*)buffer, BUFF_SIZE);
	if(status < 0) error_c2(clientfd, sockfd);
}

void server_write_str(int clientfd, int sockfd, char *buffer) {
	int status = write(clientfd, (void*)buffer, BUFF_SIZE);
	if(status < 0) error_c2(clientfd, sockfd);
}

int file_exists(char *filename) {
	FILE *file = fopen(filename, "r");
	return file != NULL;
}

int value_of(char *str) {
	int count = 0;
	int len = strlen(str);
	for(int i = 0; i < len; i++) {
		if(isdigit(str[i])) 
			count = count * 10 + (str[i] - '0');
		else break;
	}
	return count;
}

int get_popen_result(char *command) {
	FILE *output = popen(command, "r");
	if(output == NULL) return -1;

	char result[10];
	fgets(result, 10, output);

	int count = value_of(result);
	pclose(output);
	return count;
}

void client_read(int sockfd, void *msg, int size) {
	int status = read(sockfd, msg, size);
	if(status < 0) error_c(sockfd);
}

void client_write(int sockfd, const void *msg, int size) {
	int status = write(sockfd, msg, size);
	if(status < 0) error_c(sockfd);
}

void server_read(int clientfd, int sockfd, void *msg, int size) {
	int status = read(clientfd, msg, size);
	if(status < 0) error_c2(clientfd, sockfd);
}

void server_write(int clientfd, int sockfd, const void *msg, int size) {
	int status = write(clientfd, msg, size);
	if(status < 0) error_c2(clientfd, sockfd);
}

/* 3 */

int compare_int(const void *a, const void *b) {
	return *(const int*)a - *(const int*)b;
}