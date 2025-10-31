#include <netdb.h>

void gethostbyname_ts(struct hostent *host, const char *name) {
  int i;
  struct hostent *sharedhost;

  P(&mutex);
  sharedhost = gethostbyname(name);
  strcpy(host->h_name, sharedhost->h_name);

  for (i = 0; sharedhost->h_aliases[i] != NULL; i++) {
    strcpy(host->h_aliases[i], sharedhost->h_aliases[i]);
  }
  host->h_alias[i] = NULL;

  host->h_addrtype = sharedhost->h_addrtype;
  host->h_length = sharedhost->h_length;

  for (i = 0; sharedhost->h_addr_list[i] != NULL; i++) {
    strcpy(host->h_addr_list[i], sharedhost->h_addr_list[i]);
  }
  host->h_addr_list[i] = NULL;
  V(&mutex);
}
