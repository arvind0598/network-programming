#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_server_default();
  int sockfd = socket_tcp_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  pid_t parent = fork();
  if(parent < 0) error_c2(clientfd, sockfd);
  
  if(parent) {
    printf("The parent p_id is %d\n", getpid());
    while(1) {
      server_read_str(clientfd, sockfd, buffer);
      if(!strcmp(buffer, "stop")) break;
      puts(buffer);
    }
  }
  else {
    printf("The child p_id is %d\n", getpid());
    while(1) {
      stdin_get_str(buffer);
      server_write_str(clientfd, sockfd, buffer);
      if(!strcmp(buffer, "stop")) break;
    }
  }

  close(clientfd);
  close(sockfd);
  return 0;
}