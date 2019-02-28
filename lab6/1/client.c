#include "../../lab.h"

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  printf("Enter username.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);

  printf("Enter password.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);
  
  int login_status = client_read_int(sockfd);
  printf("%s\n", login_status ? "Credentials valid" : "Credentials invalid.");
  if(!login_status) error_c(sockfd);

  client_read_str(sockfd, buffer);
  printf("%s", buffer);

  int exit = 0;
  while(1) {
    int option = client_get_write_int(sockfd);
    switch(option) {
      case 1: {
        printf("Enter amount to debit.\n");
        int amount = client_get_write_int(sockfd);
        int trans_success = client_read_int(sockfd);
        printf("%s\n", trans_success ? "Transaction successful." : "Transaction failed.");
        break;
      }
      case 2: {
        printf("Enter amount to credit.\n");
        int amount = client_get_write_int(sockfd);
        int trans_success = client_read_int(sockfd);
        printf("%s\n", trans_success ? "Transaction successful." : "Transaction failed.");
        break;
      }
      case 3: {
        int balance = client_read_int(sockfd);
        printf("You have Rs.%d remaining.\n", balance);
        break;
      }
      default: {
        int commit_status = client_read_int(sockfd);
        printf("%s\n", commit_status ? "Logged out successfully." : "Could not commit transactions.");
        exit = 1;
      }
    }

    if(exit) break;
  }

  close(sockfd);
  return 0;
}