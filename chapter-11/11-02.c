#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
  unsigned int host;
  struct in_addr addr;

  if (argc != 2) {
    printf("Enter a hexadecimal adress value\n");
    exit(0);
  }
  
  if (sscanf(argv[1], "%x", &host) != 1) {
    printf("Enter a hexadecimal adress value\n");
    exit(0);
  }

  addr.s_addr = htonl(host);

  printf("%s\n", inet_ntoa(addr));

  exit(0);
}


  




    
