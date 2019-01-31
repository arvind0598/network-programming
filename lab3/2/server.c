#include "../../lab.h"

int sockfd;
SA_IN client;
int client_len;

void send_permutations(char *s, int l, int r) {
  if(l == r)
    udp_send(sockfd, s, BUFF_SIZE, 0, (const SA*)&client, client_len);
  else {
    for(int i = l; i <= r; i++) {
      SWAP(s[l], s[i]);
      send_permutations(s, l + 1, r);
      SWAP(s[l], s[i]);
    }
  }
}

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_server_default();
  sockfd = socket_udp_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));

  while(1) {
    client_len = sizeof(client);
    udp_recv(sockfd, buffer, BUFF_SIZE, 0, (SA*)&client, &client_len);
    if(!strcmp(buffer, "stop")) break;
    puts(buffer);    
    send_permutations(buffer, 0, strlen(buffer) - 1);
    udp_send(sockfd, "????", BUFF_SIZE, 0, (const SA*)&client, client_len);
  }

  close(sockfd);
  return 0;
}