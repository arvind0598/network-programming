#include "../../lab.h"

enum options{alpha, digit};

void strrev(char *str) {
  if (!str || ! *str) return;

  int i = strlen(str) - 1, j = 0;

  char ch;
  while (i > j) {
    ch = str[i];
    str[i--] = str[j];
    str[j++] = ch;
  }
}

void strsort(char *str) {
  int n = strlen(str);
  for (int i = 0; i < n - 1; i++)
    for (int j = i + 1; j < n; j++)
      if (str[i] > str[j]) SWAP(str[i], str[j]);
}

void sort_string(char *str, enum options opt) {
  char x[BUFF_SIZE];
  int n = strlen(str);
  int k = 0;

  for(int i = 0; i < n; i++) 
    if((opt == alpha && isalpha(str[i])) || (opt == digit && isdigit(str[i])))
      x[k++] = str[i];

  x[k] = '\0';
  strsort(x);
  if(opt == alpha) strrev(x);
  strcpy(str, x);
}

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_server_default();
  int sockfd = socket_tcp_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA *)&client, &client_len);
  server_read_str(clientfd, sockfd, buffer);

  pid_t parent = fork();
  if(parent < 0) error_c2(clientfd, sockfd);

  if(parent) {
    sort_string(buffer, alpha);
    char message[BUFF_SIZE];
    sprintf(message, "Message from parent %d: %s", getpid(), buffer);
    server_write_str(clientfd, sockfd, message);
  }
  else {
    sort_string(buffer, digit);
    char message[BUFF_SIZE];
    sprintf(message, "Message from child %d: %s", getpid(), buffer);
    server_write_str(clientfd, sockfd, message);
  }

  close(clientfd);
  close(sockfd);
  return 0;
}