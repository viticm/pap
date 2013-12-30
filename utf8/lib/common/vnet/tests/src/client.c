#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api/vnet.h"

void strtest(const void* str) {
  printf("str: %s\n", str);
}

int32_t main(int32_t argc, char* argv[]) {
  int32_t socketid = 0;
  bool result = true;
  const char* sendtext = "hello server";
  vnet_strtest(socketid, sendtext);
  vnet_socketbase_send(socketid, sendtext, 10, 0);
  socketid = vnet_socketbase_create();
  if (SOCKET_ERROR == socketid) return 1;
  printf("socket create is success\n");
  char serverip[] = "127.0.0.1";
  uint16_t serverport = 3138;
  result = vnet_socketbase_connect(socketid, serverip, serverport);
  printf("result: %d\n", result);
  if (!result) return 1;
  printf("connect server ip: %s, port: %d success\n", serverip, serverport);
  while (true) {
    int32_t sendcount = 0;
    printf("loop...\n");
    strtest(sendtext);
    sendcount = vnet_socketbase_send(socketid, 
                                     sendtext, 
                                     strlen(sendtext) + 1, 
                                     0);
    if (sendcount != strlen(sendtext) + 1) {
      printf("send error\n");
    }
    else {
      printf("send success\n");
    }
    char buffer[FILENAME_MAX];
    memset(buffer, '\0', sizeof(buffer));
    printf("loop end...\n");
    if (SOCKET_ERROR == vnet_socketbase_receive(socketid, 
                                                buffer, 
                                                sizeof(buffer) - 1, 
                                                0)) {
      printf("error receive\n");
    }
    else {
      printf("receive success: %s\n", buffer);
    }

    sleep(1000);
  }
  vnet_socketbase_close(socketid);
  return 0;
}
