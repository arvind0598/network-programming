#include "../../lab.h"

void write_into_file(char *filename, char *message) {
  FILE *file = fopen(filename, "a");
  fprintf(file, "%s ", message);
  fclose(file);
}

void show_contents(char *filename, char *buffer) {
  FILE *file = fopen(filename, "r");
  int i = 0;
  char c;
  while((c = fgetc(file)) != EOF) {
    buffer[i++] = c;
  }
  buffer[i] = 0;
}

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  server_read_str(clientfd, sockfd, buffer);
  buffer[strlen(buffer) - 1] = 0;
  int is_exists = file_exists(buffer);
  server_write_int(clientfd, sockfd, is_exists);
  
  char filename[BUFF_SIZE];
  strcpy(filename, buffer);

  if(!is_exists) error_c2(clientfd, sockfd);

  show_contents(filename, buffer);
  pid_t parent = fork();
  if(parent < 0) error_c2(clientfd, sockfd);

  if(parent) {
    int n = strlen(buffer);
    FILE *file = fopen(filename, "a");
    fprintf(file, "\n");
    for(int i = 0; i < n; i++) {
      int x = isalpha(buffer[i]) ? (buffer[i] | 32) - 'a' + 1: -1;
      fprintf(file, "%d ", x);
    }
    fprintf(file, "Process ID: %d", getpid());
    fclose(file);
    server_write_int(clientfd, sockfd, 1);
  }
  else {
    int n = strlen(buffer);
    for(int i = 0; i < n; i++)
      if(islower(buffer[i]))
        buffer[i] &= ~32;
    FILE *file = fopen(filename, "a");
    fprintf(file, "\n%s Process ID: %d", buffer, getpid());
    fclose(file);
    server_write_int(clientfd, sockfd, 1);
  }

  close(clientfd);
  close(sockfd);
  return 0;
}