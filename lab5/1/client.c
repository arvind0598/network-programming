#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));
  int connect_success = client_read_int(sockfd);
  printf("%d\n", connect_success);
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);
  int write_success = client_read_int(sockfd);
  printf("Write %s.\n", write_success ? "successful" : "unsuccessful");
  close(sockfd);
  return 0;
}