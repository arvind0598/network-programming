#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_udp_default();

  while(1) {
    int server_len = sizeof(server);
    stdin_get_str(buffer);
	  udp_send(sockfd, buffer, sizeof(buffer), 0, (SA *)&server, server_len);
    if(!strcmp(buffer, "stop")) break;    
    
    udp_recv(sockfd, buffer, BUFF_SIZE, 0, (SA*)&server, &server_len);
    if(!strcmp(buffer, "stop")) break;    
    puts(buffer);
  }

  close(sockfd);
  return 0;
}