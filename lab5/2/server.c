#include "../../lab.h"
#include <time.h>

int check_anagram(char *a, char *b) {
  if(strlen(a) != strlen(b)) return 0;

  int count_a[26] = {0};
  int count_b[26] = {0};
  const int bitshift = 1 << 5;

  for(int i = 0; i < strlen(a); i++) {
    a[i] |= bitshift;
    b[i] |= bitshift;
    count_a[a[i] - 'a'] += 1;
    count_b[b[i] - 'a'] += 1;
  }

  for(int i = 0; i < 26; i++) {
    if(count_a[i] != count_b[i]) return 0;
  }

  return 1;
}

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  time_t curr_time;
  struct tm *local_time;
  
  while(1) {
    SA_IN client;
    int client_len = sizeof(client);
    int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

    curr_time = time(NULL);
    local_time = localtime(&curr_time);
    char ip_addr[BUFF_SIZE];
    int port = ntohs(client.sin_port);
    inet_ntop(AF_INET, &client.sin_addr, ip_addr, sizeof(ip_addr));
    printf("%s:%d connected at %s", ip_addr, port, asctime(local_time));

    char other[BUFF_SIZE];
    server_read_str(clientfd, sockfd, buffer);
    strcpy(other, buffer);
    server_read_str(clientfd, sockfd, buffer);
    int status = check_anagram(buffer, other);
    server_write_int(clientfd, sockfd, status);
    close(clientfd);
  }

  close(sockfd);
  return 0;
}