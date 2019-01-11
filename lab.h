#pragma once

#define _BSD_SOURCE

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>/* 2 */
#include <ctype.h>/* 2 */

#define PORT 5052
#define BUFF_SIZE 100
#define SHOW(a, n) for(int i = 0; i < n; i++) printf("%d ", a[i])
#define SWAP(a,b) if(a!=b) {a^= b; b^=a; a^=b;}

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

// error handling

void error();
void error_c(int sockfd);
void error_c2(int sockfd, int sockfd2);

// saving time

int socket_s(int family, int type, int protocol);
int bind_s(int sockfd, const SA *server, int size);
int listen_s(int sockfd, int backlog);
int connect_s(int sockfd, SA *server, int size);
int accept_s(int sockfd, SA *client, socklen_t *size);

// client functions

int client_read_int(int sockfd);
void client_read_str(int sockfd, char *buffer);/* 2 */
int *client_read_intarr(int sockfd, int n);

void client_write_int(int sockfd, int x);
void client_write_str(int sockfd, char *buffer);/* 2 */
void client_write_intarr(int sockfd, int *arr, int n);

int client_get_write_int(int sockfd);

// server functions

int server_read_int(int clientfd, int sockfd);
void server_read_str(int clientfd, int sockfd, char *buffer);/* 2 */
int *server_read_intarr(int clientfd, int sockfd, int n);

void server_write_int(int clientfd, int sockfd, int x);
void server_write_str(int clientfd, int sockfd, char *buffer);/* 2 */
void server_write_intarr(int clientfd, int sockfd, int *arr, int n);

// udp

int udp_send(int sockfd, const void* msg, int len, int flags, const SA* to, int tolen);
int udp_recv(int sockfd, void *msg, int len, int flags, SA* from, int *fromlen);

// socket stuff

SA_IN sa_init(int family, int port, int address);
SA_IN sa_server_default();
SA_IN sa_client_default();

// utitilies

int *stdin_get_intarr(int n);
void stdin_get_str(char *buffer);/* 2 */

// file handling

int file_exists(char *filename);/* 2 */
int search_in_file(char *filename, char *word);/* 2 */
int replace_in_file(char *filename, char *old_word, char *new_word);/* 2 */
int sort_file_ascii(char *filename);/* 2 */