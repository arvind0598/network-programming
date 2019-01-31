#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  
  // treat agent as server  
  int sockfd = socket_tcp_default();
  SA_IN agent = sa_init(AF_INET, htons(AGENT_PORT), htonl(INADDR_ANY));
  bind_s(sockfd, (const SA*)&agent, sizeof(agent));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  server_read_str(clientfd, sockfd, buffer);

  // treat agent as client
  int newfd = socket_tcp_default();
  SA_IN server = sa_client_default();
  connect_s(newfd, (SA*)&server, sizeof(server));

  client_write_str(newfd, buffer);
  client_read_str(newfd, buffer);
  close(newfd);

  // send response back to client

  server_write_str(clientfd, sockfd, buffer);
  close(clientfd);
  close(sockfd);
  return 0;
}