#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "api/vnet.h"

int32_t main(int32_t argc, char* argv[]) {
  int32_t socketid = 0;
  bool result = true;
  const char* serverip = "127.0.0.1";
  uint16_t serverport = 3699;
  const char* sendtext = "hello server";

  socketid = vnet_socketbase_create();
  if (SOCKET_ERROR == socketid) {
    printf("socket create is failed\n");
    return 1;
  }
  else {
    printf("socket create is success, socketid: %d\n", socketid);
  }
  result = vnet_socketbase_connect(socketid, serverip, serverport);
  if (!result) {
    printf("connect server ip: %s, port: %d failed\n", serverip, serverport);
    return 1;
  }
  else {
    printf("connect server ip: %s, port: %d success\n", serverip, serverport);
  }
  while (true) {
    int32_t sendcount = 0;
    //printf("last errno: %d\n", vnet_socketbase_getlast_errorcode());
    sendcount = vnet_socketbase_send(socketid, 
                                     sendtext, 
                                     strlen(sendtext) + 1, 
                                     0);
    if (sendcount != strlen(sendtext) + 1) {
      printf("send error\n");
    }
    else {
      printf("send success, sendtext: %s\n", sendtext);
    }
    char buffer[FILENAME_MAX];
    memset(buffer, '\0', sizeof(buffer));
    if (SOCKET_ERROR == vnet_socketbase_receive(socketid, 
                                                buffer, 
                                                sizeof(buffer) - 1, 
                                                0)) {
      printf("error receive\n");
    }
    else {
      printf("receive success: %s\n", buffer);
    }
    printf("client loop...\n");
    sleep(10000);
  }
  vnet_socketbase_close(socketid);
  return 0;
}
