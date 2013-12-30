#include <stdio.h>
#include "api/vnet.h"

int32_t main(int32_t argc, char* argv[]) {
  int32_t socketid = 0;
  socketid = vnet_socketbase_create(AF_INET);
  vnet_socketbase_close(socketid);
  printf("socketid: %d\n", socketid);
}
