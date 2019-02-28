#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len;
  int clientfd = accept_s(sockfd, (SA*)&server, &client_len);

  pid_t parent = fork();
  if(parent < 0) error_c2(clientfd, sockfd);

  if(parent) {
    while(1) {
      stdin_get_str(buffer);
      server_write_str(clientfd, sockfd, buffer);
      if(!strcmp(buffer, "stop")) break;
    }
  }
  else {
    while(1) {
      server_read_str(clientfd, sockfd, buffer);
      if(!strcmp(buffer, "stop\n")) {
        server_write_str(clientfd, sockfd, "stop\n");
        break;
      }
      printf("Client: %s", buffer);
    }
  }

  close(clientfd);
  close(sockfd);
  return 0;
}