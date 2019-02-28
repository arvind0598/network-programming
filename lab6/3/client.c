#include "../../lab.h"

int show_file_contents(char *filename) {
	char command[100];
	sprintf(command, "cat %s", filename);
	system(command);
	return 1;
}

int main() {
  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_client_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  printf("Enter file name.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);

  int is_exists = client_read_int(sockfd);
  if(!is_exists) {
    printf("The file does not exist.\n");
    close(sockfd);
    return 0;
  }

  int is_complete = client_read_int(sockfd) && client_read_int(sockfd);
  if(!is_complete) error_c(sockfd);

  show_file_contents(buffer);
  close(sockfd);
  return 0;  
}