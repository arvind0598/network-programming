#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct account {
  int id;
  char username[20];
  char password[20];
  int balance;
};

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

int main() {
  struct account accounts[5];
  for(int i = 0; i < 5; i++) {
    scanf("%d %s %s %d", &accounts[i].id, accounts[i].username, accounts[i].password, &accounts[i].balance);
    encrypt_password(accounts[i].password, 3);
  }
  FILE *ptr = fopen("records", "wb");
  fwrite(accounts, sizeof(accounts), 1, ptr);
  fclose(ptr);

  ptr = fopen("records", "rb");
  struct account more[5];
  fread(more, sizeof(more), 1, ptr);
  for(int i = 4; i >= 0; i--) {
    printf("%d %s %s %d\n", more[i].id, more[i].username, more[i].password, more[i].balance);
  }
  fclose(ptr);

  return 0;
}