#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);
  
  client_read_str(sockfd, buffer);
  puts(buffer);
  client_read_str(sockfd, buffer);
  puts(buffer);

  close(sockfd);
  return 0;
}