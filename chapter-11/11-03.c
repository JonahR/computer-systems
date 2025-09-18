#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct in_addr addr;
  int host;
  
  if (argc != 2) {
    printf("Enter a valid ip address\n");
    exit(0);
  }

  if (inet_aton(argv[1], &addr) != 1) {
    printf("Enter a valid ip address\n");
    exit(0);
  }

  printf("0x%x\n", ntohl(addr.s_addr));
  exit(0);
}
