#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "api/vnet.h"

int32_t main(int32_t argc, char* argv[]) {
  int32_t listen_socketid = 0;
  int32_t accept_socketid = 0;
  uint32_t listenport = 3699;
  bool result = true;
  
  listen_socketid = vnet_socketbase_create();
  if (SOCKET_ERROR == listen_socketid) {
    printf("create socket is failed\n");
  }
  else {
    printf("create socket is success, listen socketid: %d\n", listen_socketid);
  }
  result = vnet_socketbase_set_reuseaddr(listen_socketid, true);
  if (!result) {
    printf("set reuse addr is failed\n");
    return 1;
  }
  else {
    printf("set reuse addr is success\n");
  }
  result = vnet_socketbase_bind(listen_socketid, listenport);
  if (!result) {
    printf("socket bind is failed, port: %d\n", listenport);
    return 1;
  }
  else {
    printf("socket bind is success, port: %d\n", listenport);
  }
  result = vnet_socketbase_listen(listen_socketid, 3);
  if (!result) {
    printf("socket listen is failed\n");
    return 1;
  }
  else {
    printf("socket listen is success\n");
  }

  printf("waiting client connect...\n");
  //single client can connect, you can use array to save client information
  accept_socketid = vnet_socketbase_fastaccept(listen_socketid);
  if (SOCKET_ERROR == accept_socketid) {
    printf("socket accept failed\n");
    return 1;
  }
  else {
    printf("socket accept success.\n");
  }

  while(true) {
    char revbuf[255];
    //accept_socketid = vnet_socketbase_fastaccept(listen_socketid);
    memset(revbuf, '\0', sizeof(revbuf));
    if (SOCKET_ERROR == vnet_socketbase_receive(accept_socketid, 
                                                revbuf, 
                                                sizeof(revbuf) - 1, 
                                                0)) {
      printf("error receive, accept socketid: %d\n", accept_socketid);
    }
    else {
      printf("receive success: %s, accept socketid: %d\n", 
             revbuf, 
             accept_socketid);
    }
    const char* buffer = "hello, socket is work.";
    if(vnet_socketbase_send(accept_socketid, buffer, strlen(buffer) + 1, 0) 
        != strlen(buffer) + 1) {
      printf("send error, accept socketid: %d\n", accept_socketid);
    }
    else {
      printf("send success, buffer: %s, accept socketid: %d\n", 
             buffer,
             accept_socketid);
    }
    //vnet_socketbase_close(accept_socketid);
    //sleep(10);
  }
  vnet_socketbase_close(listen_socketid);
  return 0;
}
