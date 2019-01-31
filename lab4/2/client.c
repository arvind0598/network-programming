#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_init(AF_INET, htons(AGENT_PORT), inet_addr("127.0.0.1"));
  connect_s(sockfd, (SA*)&server, sizeof(server));

  printf("Enter domain name.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);

  client_read_str(sockfd, buffer);
  printf("%s\n", buffer);

  close(sockfd);
  return 0;
}