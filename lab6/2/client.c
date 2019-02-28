#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  // SA_IN server = sa_init(AF_INET, htons(80), inet_addr("192.168.43.25"));
  SA_IN server = sa_client_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  pid_t parent = fork();
  if(parent < 0) error_c(sockfd);

  if(parent) {
    while(1) {
      stdin_get_str(buffer);
      client_write_str(sockfd, buffer);
      if(!strcmp(buffer, "stop\n")) break;
    }
  }
  else {
    while(1) {
      client_read_str(sockfd, buffer);
      if(!strcmp(buffer, "stop\n")) {
        client_write_str(sockfd, "stop\n");
        break;
      }
      printf("Server: %s", buffer);
    }
  }

  close(sockfd);
  return 0;
}