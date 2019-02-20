#include "../../lab.h"
#include <sys/mman.h>

void *setup_shared_memory(ssize_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  return mmap(NULL, size, protection, visibility, 0, 0);
}

void setup_file(char *filename) {
  FILE *file = fopen(filename, "w");
  fprintf(file, "%s ", "Manipal");
  fclose(file);
}

void write_into_file(char *filename, char *message) {
  FILE *file = fopen(filename, "a");
  fprintf(file, "%s ", message);
  fclose(file);
}

void show_contents(char *filename, char *buffer) {
  FILE *file = fopen(filename, "r");
  int i = 0;
  char c;
  while((c = fgetc(file)) != EOF) {
    buffer[i++] = c;
  }
  buffer[i] = 0;
}

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  setup_file("amazing.txt");

  int max_connections = 2;
  int *connections = (int*)setup_shared_memory(sizeof(int));
  memset(connections, 0, sizeof(int));
  printf("%d\n", *connections);
  
  while(1) {
    int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

    if(*connections >= max_connections) {
      // drop connections and terminate program
      *connections = -1;
      server_write_int(clientfd, sockfd, 0);
      error_c2(clientfd, sockfd);
    }
    else {
      // accept connection
      char ip_addr[BUFF_SIZE];
      int port = ntohs(client.sin_port);
      inet_ntop(AF_INET, &client.sin_addr, ip_addr, sizeof(ip_addr));      
      *connections += 1;
      server_write_int(clientfd, sockfd, *connections);
      printf("%s:%d has just connected.\n", ip_addr, port);
    }
    
    printf("Currently %d clients connected.\n", *connections);

    pid_t parent = fork();
    if(parent < 0) error_c2(clientfd, sockfd);

    if(parent) {
      close(clientfd);
    }
    else {
      close(sockfd);
      client_read_str(clientfd, buffer);
      puts(buffer);

      // check if should proceed
      if(*connections < 0) {
        client_write_int(clientfd, 0);
        error_c(clientfd);
      }
      else {
        // write to file here
        write_into_file("amazing.txt", buffer);
        client_write_int(clientfd, 1);
        close(clientfd);
        *connections -= 1;
      }
      exit(0);
    }

    show_contents("amazing.txt", buffer);
    printf("Current file contents: %s\n", buffer);
  }
  close(sockfd);
  return 0;
}