#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  pid_t parent = fork();
  if(parent < 0) error_c(sockfd);

  if(parent) {
    printf("The parent p_id is %d\n", getpid());
    while(1) {
      client_read_str(sockfd, buffer);
      if(!strcmp(buffer, "stop")) {
        client_write_str(sockfd, "stop");
        break;
      }
      puts(buffer);
    }
  }
  else {
    printf("The child p_id is %d\n", getpid());
    while(1) {
      stdin_get_str(buffer);
      client_write_str(sockfd, buffer);
      if(!strcmp(buffer, "stop")) break;
    }
  }

  close(sockfd);
  return 0;
}