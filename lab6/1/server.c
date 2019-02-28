#include "../../lab.h"

/* 
  DATA STORED INITIALLY 
  1 arvind0598 ab123ab 5000
  2 de.arth de!!123 2500
  3 naruCOOL longpassword 6000
  4 stars98 papergrid0! 1200
  5 deathmaster greenboi 500
*/

struct account {
  int id;
  char username[20];
  char password[20];
  int balance;
};

void trim(char * s) {
  char * p = s;
  int l = strlen(p);

  while(isspace(p[l - 1])) p[--l] = 0;
  while(* p && isspace(* p)) ++p, --l;

  memmove(s, p, l + 1);
}

void encrypt_password(char *a, int x) {
  int n = strlen(a);
  for(int i = 0; i < n; i++) {
    if(isupper(a[i]))
      a[i] = (((a[i] - 'A') + x) % 26) + 'A';
    else if(islower(a[i]))
      a[i] = (((a[i] - 'a') + x) % 26) + 'a';
    else continue;
  }
}

int check_credentials(char *username, char *password) {
  FILE *file = fopen("records", "rb");
  struct account accounts[5];
  fread(accounts, sizeof(accounts), 1, file);
  fclose(file);
  for(int i = 0; i < 5; i++) {
    printf("%s, %s and %s, %s\n", username, accounts[i].username, password, accounts[i].password);
    if(!strcmp(username, accounts[i].username) && !strcmp(password, accounts[i].password)) {
      return accounts[i].id + 1;
    }
  }
  return 0;
}

void get_account_details(struct account *acc, int id) {
  FILE *file = fopen("records", "rb");
  struct account accounts[5];
  fread(accounts, sizeof(accounts), 1, file);
  fclose(file);
  memcpy(acc, (const void*)&accounts[id - 2], sizeof(struct account));
}

int commit_transactions(struct account *acc) {
  FILE *file = fopen("records", "rb");
  struct account accounts[5];
  fread(accounts, sizeof(accounts), 1, file);
  fclose(file);

  memcpy((void *)&accounts[acc->id - 1], acc, sizeof(struct account));
  for(int i = 0; i < 5; i++) {
    printf("%d %s %s %d\n", accounts[i].id, accounts[i].username, accounts[i].password, accounts[i].balance);
  }
  file = fopen("records", "rw");
  fwrite(accounts, sizeof(accounts), 1, file);
  fclose(file);
  return 1;
}

int main() {
  char buffer[BUFF_SIZE];
  SA_IN server = sa_server_default();
  int sockfd = socket_tcp_default();
  bind_s(sockfd, (const SA*)&server, sizeof(server));
  listen_s(sockfd ,1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  char username[BUFF_SIZE];
  server_read_str(clientfd, sockfd, username);
  trim(username);

  char password[BUFF_SIZE];
  server_read_str(clientfd, sockfd, password);
  trim(password);
  encrypt_password(password, 3);

  int credentials_valid = check_credentials(username, password);
  server_write_int(clientfd, sockfd, credentials_valid);
  printf("%s\n", credentials_valid ? "Credentials valid" : "Credentials invalid.");
  if(!credentials_valid) error_c2(clientfd, sockfd);

  const char menu[] = {"1. Debit\n2. Credit\n3. View Balance\n4. Logout.\n"};
  server_write_str(clientfd, sockfd, buffer);

  struct account acc;
  get_account_details(&acc, credentials_valid);
  printf("%d %s %s %d\n", acc.id, acc.username, acc.password, acc.balance);
  int exit = 0;

  while(1) {
    int option = server_read_int(clientfd, sockfd);
    switch(option){
      case 1: {
        int amount = server_read_int(clientfd, sockfd);
        if(acc.balance < amount) {
          server_write_int(clientfd, sockfd, 0);
        }
        else {
          acc.balance -= amount;
          server_write_int(clientfd, sockfd, 1);
        }
        break;
      }
      case 2: {
        int amount = server_read_int(clientfd, sockfd);
        acc.balance += amount;
        server_write_int(clientfd, sockfd, 1);
        break;
      }
      case 3: {
        server_write_int(clientfd, sockfd, acc.balance);
        break;
      }
      default: {
        int status = commit_transactions(&acc);
        server_write_int(clientfd, sockfd, status);
        exit = 1;
      }
    }

    if(exit) break;
  }

  close(clientfd);
  close(sockfd);
  return 0;
}