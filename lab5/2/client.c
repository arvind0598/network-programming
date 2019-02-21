#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  printf("Enter first word.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);

  printf("Enter second word.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);
  
  int status = client_read_int(sockfd);
  printf("Strings are %sanagrams.", status ? "":"not ");
  close(sockfd);
  return 0;
}