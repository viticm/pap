#include <stdio.h>
#include <string.h>
#include "api/vnet.h"

int32_t main(int32_t argc, char* argv[]) {
  int32_t socketid = 0;
  bool result = true;
  socketid = vnet_socketbase_create();
  result = vnet_socketbase_set_reuseaddr(socketid, true);
  if (!result) return 1;
  result = vnet_socketbase_bind(socketid, 3138);
  if (result) printf("socket bind is success\n");
  result = vnet_socketbase_listen(socketid, 3);
  if (result) printf("socket listen is success\n");
  socketid = vnet_socketbase_accept(socketid, 3138);
      
  while(true) {
    char revbuf[255];
    memset(revbuf, '\0', sizeof(revbuf));
    if (SOCKET_ERROR == vnet_socketbase_receive(socketid, 
                                                revbuf, 
                                                sizeof(revbuf) - 1, 
                                                0)) {
      printf("error receive\n");
    }
    else {
      printf("receive success: %s\n", revbuf);
    }
    const char* buffer = "hello, socket is work.";
    if(vnet_socketbase_send(socketid, buffer, strlen(buffer) + 1, 0) 
        != strlen(buffer) + 1) {
      printf("send error\n");
    }
    else {
      printf("send success\n");
    }
    sleep(3000);
  }
  vnet_socketbase_close(socketid);
  printf("socketid: %d\n", socketid);
  return 0;
}
