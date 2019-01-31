#include "../server.h"

int main() {

  // setup database
  struct dns_map *records = malloc(5 * sizeof(struct dns_map));
  create_dns_records(records);

  // setup sockets
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  // perform dns query
  server_read_str(clientfd, sockfd, buffer);
  find_ip_by_domain(records, 5, buffer, buffer);
  server_write_str(clientfd, sockfd, buffer);

  close(clientfd);
  close(sockfd);
}