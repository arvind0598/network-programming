#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_server_default();
  int sockfd = socket_udp_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));

  SA_IN client;

  while(1) {
    int client_len = sizeof(client);
    udp_recv(sockfd, buffer, BUFF_SIZE, 0, (SA*)&client, &client_len);
    if(!strcmp(buffer, "stop")) break;
    puts(buffer);    

    stdin_get_str(buffer);    
    udp_send(sockfd, buffer, BUFF_SIZE, 0, (const SA*)&client, client_len);
    if(!strcmp(buffer, "stop")) break;  
  }

  close(sockfd);
  return 0;
}