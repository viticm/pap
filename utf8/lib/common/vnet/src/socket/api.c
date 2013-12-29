#include "socket/api.h"
#include "file/api.h"

#if defined(__LINUX__)
extern int32_t errno;
#endif
char errormessage[FILENAME_MAX];

int32_t socketapi_socketex(int32_t domain, int32_t type, int32_t protocol) {
  
  int32_t socketid = socket(domain, type, protocol);

  if (socketid == ID_INVALID) {
#if defined(__LINUX__)
    switch (errno) {
      case EPROTONOSUPPORT :
      case EMFILE : 
      case ENFILE : 
      case EACCES : 
      case ENOBUFS : 
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : { 
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEAFNOSUPPORT : {
        strncpy(errormessage, "WSAEAFNOSUPPORT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEMFILE : {
        strncpy(errormessage, "WSAEMFILE", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEPROTONOSUPPORT : {
        strncpy(errormessage, "WSAEPROTONOSUPPORT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEPROTOTYPE : {
        strncpy(errormessage, "WSAEPROTOTYPE", sizeof(errormessage) - 1);
        break;
      }
      case WSAESOCKTNOSUPPORT : {
        strncpy(errormessage, "WSAESOCKTNOSUPPORT", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
  }
  return socketid;
}

bool socketapi_bindex(int32_t socketid, 
                      const struct sockaddr* addr, 
                      uint32_t addrlength) {
  

  if (SOCKET_ERROR == bind(socketid, addr, addrlength)) {
#if defined(__LINUX__)
    switch (errno) 
    {
      case EADDRINUSE :
      case EINVAL : 
      case EACCES : 
      case ENOTSOCK : 
      case EBADF : 
      case EROFS : 
      case EFAULT : 
      case ENAMETOOLONG : 
      case ENOENT : 
      case ENOMEM : 
      case ENOTDIR : 
      case ELOOP : 
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : { 
        strncpy(errormessage, "WSAESOCKTNOSUPPORT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEADDRINUSE : {
        strncpy(errormessage, "WSAEADDRINUSE", sizeof(errormessage) - 1);
        break;
      }
      case WSAEADDRNOTAVAIL : {
        strncpy(errormessage, "WSAEADDRNOTAVAIL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
    return false;
  }
  return true;
}

bool socketapi_connectex(int32_t socketid, 
                         const struct sockaddr * addr, 
                         uint32_t addrlength) {
  

  if (SOCKET_ERROR == connect(socketid,addr,addrlength)) {
#if defined(__LINUX__)
    switch (errno) {
      case EALREADY : 
      case EINPROGRESS : 
      case ECONNREFUSED : 
      case EISCONN : 
      case ETIMEDOUT : 
      case ENETUNREACH : 
      case EADDRINUSE : 
      case EBADF : 
      case EFAULT : 
      case ENOTSOCK : 
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEADDRINUSE : {
        strncpy(errormessage, "WSAEADDRINUSE", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR : {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEALREADY : {
        strncpy(errormessage, "WSAEALREADY", sizeof(errormessage) - 1);
        break;
      }
      case WSAEADDRNOTAVAIL : {
        strncpy(errormessage, "WSAEADDRNOTAVAIL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEAFNOSUPPORT : {
        strncpy(errormessage, "WSAEAFNOSUPPORT", sizeof(errormessage) - 1);
        break;
      }
      case WSAECONNREFUSED : {
        strncpy(errormessage, "WSAECONNREFUSED", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEISCONN : {
        strncpy(errormessage, "WSAEISCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETUNREACH : {
        strncpy(errormessage, "WSAENETUNREACH", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAETIMEDOUT : {
        strncpy(errormessage, "WSAETIMEDOUT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEWOULDBLOCK  : {
        strncpy(errormessage, "WSAEWOULDBLOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
    return false;
  }
  return true;
}

bool socketapi_listenex(int32_t socket, uint32_t backlog) {
  
  if (SOCKET_ERROR == listen(socket, backlog)) {
#if defined(__LINUX__)
    switch (errno) {
      case EBADF : 
      case ENOTSOCK :
      case EOPNOTSUPP :
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEADDRINUSE : {
        strncpy(errormessage, "WSAEADDRINUSE", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEISCONN : {
        strncpy(errormessage, "WSAEISCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEMFILE : {
        strncpy(errormessage, "WSAEMFILE", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEOPNOTSUPP : {
        strncpy(errormessage, "WSAEOPNOTSUPP", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
    return false;
  }
  return true;
}

int32_t socketapi_acceptex(int32_t socket, 
                           struct sockaddr* addr, 
                           uint32_t* addrlength) {

#if defined(__LINUX__)
  int32_t client = accept(socket, addr, addrlength);
#elif defined(__WINDOWS__)
  int32_t client = accept(socket, addr, (int32_t*)addrlength);
#endif
  
  if (ID_INVALID == client) {
#if defined(__LINUX__)
    switch (errno) {
      case EWOULDBLOCK : {
        strncpy(errormessage, "EWOULDBLOCK", sizeof(errormessage) - 1);
        break;
      }
      case ECONNRESET : {
        strncpy(errormessage, "ECONNRESET", sizeof(errormessage) - 1);
        break;
      }
      case ECONNABORTED : {
        strncpy(errormessage, "ECONNABORTED", sizeof(errormessage) - 1);
        break;
      }
      case EPROTO : {
        strncpy(errormessage, "EPROTO", sizeof(errormessage) - 1);
        break;
      }
      case EINTR : {
        // from UNIX Network Programming 2nd, 15.6
        // with nonblocking-socket, ignore above errors
        strncpy(errormessage, "EINTR", sizeof(errormessage) - 1);
        break;
      }
      case EBADF : {
        strncpy(errormessage, "EBADF", sizeof(errormessage) - 1);
        break;
      }
      case ENOTSOCK : {
        strncpy(errormessage, "ENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case EOPNOTSUPP : {
        strncpy(errormessage, "EOPNOTSUPP", sizeof(errormessage) - 1);
        break;
      }
      case EFAULT : {
        strncpy(errormessage, "EFAULT", sizeof(errormessage) - 1);
        break;
      }
      default : {
        memset(errormessage,'\0',sizeof(errormessage));
        snprintf(errormessage, sizeof(errormessage) - 1, "error: %d", errno);
        break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR : {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEMFILE : {
        strncpy(errormessage, "WSAEMFILE", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEOPNOTSUPP : {
        strncpy(errormessage, "WSAEOPNOTSUPP", sizeof(errormessage) - 1);
        break;
      }
      case WSAEWOULDBLOCK : {
        strncpy(errormessage, "WSAEWOULDBLOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
  } else {
    //do nothing
  }
  return client;
}

bool socketapi_getsockopt_exb(int32_t socket, 
                              int32_t level, 
                              int32_t optname, 
                              void* optval, 
                              uint32_t* optlength) {
  
#if defined(__LINUX__)
  if (SOCKET_ERROR ==getsockopt(socket, level, optname, optval, optlength)) {
    switch (errno) {
      case EBADF : 
      case ENOTSOCK : 
      case ENOPROTOOPT : 
      case EFAULT : 
      default : {
        break;
      }
    }
    return false;
  }
#elif defined(__WINDOWS__)
  if (SOCKET_ERROR == getsockopt(socket, 
                                 level, 
                                 optname, 
                                 (char*)optval, 
                                 (int32_t*)optlength)) {
    int32_t error = WSAGetLastError();
    switch (error) 
    {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOPROTOOPT : {
        strncpy(errormessage, "WSAENOPROTOOPT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
    return false;
  }
#endif
  return true;
}

uint32_t socketapi_getsockopt_exu(int32_t socket, 
                                  int32_t level, 
                                  int32_t optname, 
                                  void* optval, 
                                  uint32_t* optlength) {
uint32_t result = 0;
#if defined(__LINUX__)
  if (SOCKET_ERROR == getsockopt(socket, level, optname, optval, optlength)) {
    switch (errno) {
      case EBADF : { 
        result = 1;
        break;
      }
      case ENOTSOCK : {
        result = 2;
        break;
      }
      case ENOPROTOOPT : {
        result = 3;
        break;
      }
      case EFAULT : {
        result = 4;
        break;
      }
      default : {
        result = 5;
      }
    }
  }
#elif defined(__WINDOWS__)
  if (SOCKET_ERROR == getsockopt(socket, 
                                 level, 
                                 optname, 
                                 (char*)optval, 
                                 (int32_t*)optlength)) {
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED: {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN: {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT: {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS: {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL: {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOPROTOOPT: {
        strncpy(errormessage, "WSAENOPROTOOPT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK: {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
  }
#endif
  return result;
}

bool socketapi_setsockopt_ex(int32_t socket, 
                             int32_t level, 
                             int32_t optname, 
                             const void* optval, 
                             uint32_t optlength) {
  bool result = true;
#if defined(__LINUX__)
  if (SOCKET_ERROR == setsockopt(socket, level, optname, optval, optlength)) {
    switch (errno) {
      case EBADF : 
      case ENOTSOCK : 
      case ENOPROTOOPT : 
      case EFAULT : 
      default : {
          break;
      }
    }
    result = false;
  }
#elif defined(__WINDOWS__)
  if (SOCKET_ERROR == setsockopt(socket, 
                                 level, 
                                 optname, 
                                 (char*)optval, 
                                 optlength)) {
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : { 
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETRESET : {
        strncpy(errormessage, "WSAENETRESET", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOPROTOOPT : {
        strncpy(errormessage, "WSAENOPROTOOPT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTCONN : {
        strncpy(errormessage, "WSAENOTCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
    result = false;
  }
#endif
  return result;
}

int32_t socketapi_sendex(int32_t socket, 
                         const void* buffer, 
                         uint32_t length, 
                         uint32_t flag) {
  int32_t result = 0;
#if defined(__LINUX__)
  result = send(socket, buffer, length, flag);
#elif defined(__WINDOWS__)
  result = send(socket, (const char*)buffer, length, flag);
#endif

  if (SOCKET_ERROR == result) {
#if defined(__LINUX__)
    switch (errno) {
      case EWOULDBLOCK : {
        result = kSocketErrorWouldBlock;
        break;
      }
      case ECONNRESET :
      case EPIPE :
      case EBADF : 
      case ENOTSOCK : 
      case EFAULT : 
      case EMSGSIZE : 
      case ENOBUFS : 
      default : {
        break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : { 
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEACCES : {
        strncpy(errormessage, "WSAEACCES", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR : {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETRESET : {
        strncpy(errormessage, "WSAENETRESET", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOBUFS : {
        strncpy(errormessage, "WSAENOBUFS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTCONN : {
        strncpy(errormessage, "WSAENOTCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEOPNOTSUPP : {
        strncpy(errormessage, "WSAEOPNOTSUPP", sizeof(errormessage) - 1);
        break;
      }
      case WSAESHUTDOWN : {
        strncpy(errormessage, "WSAESHUTDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEWOULDBLOCK : {
        //strncpy(errormessage, "WSAEWOULDBLOCK", sizeof(errormessage) - 1);
        result = kSocketErrorWouldBlock;
        break;
      }
      case WSAEMSGSIZE : {
        strncpy(errormessage, "WSAEMSGSIZE", sizeof(errormessage) - 1);
        break;
      }
      case WSAEHOSTUNREACH : {
        strncpy(errormessage, "WSAEHOSTUNREACH", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAECONNABORTED : {
        strncpy(errormessage, "WSAECONNABORTED", sizeof(errormessage) - 1);
        break;
      }
      case WSAECONNRESET : {
        strncpy(errormessage, "WSAECONNRESET", sizeof(errormessage) - 1);
        break;
      }
      case WSAETIMEDOUT : {
        strncpy(errormessage, "WSAETIMEDOUT", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
  } 
  else if (0 == result) {
    //do nothing
  }
  return result;
}


int32_t socketapi_sendtoex(int32_t socket, 
                           const void* buffer, 
                           int32_t length, 
                           uint32_t flag, 
                           const struct sockaddr* to, 
                           int32_t tolength) {
  int32_t result = 0;
#if defined(__LINUX__)
  result = sendto(socket, buffer, length, flag, to, tolength);
#elif defined(__WINDOWS__)
  result = sendto(socket, (const char*)buffer,length, flag, to, tolength);
#endif

  if (SOCKET_ERROR == result) {
#if defined(__LINUX__)
    switch (errno) {
      case EWOULDBLOCK : {
        result = 0;
        break;
      }
      case ECONNRESET :
      case EPIPE :
      case EBADF : 
      case ENOTSOCK : 
      case EFAULT : 
      case EMSGSIZE : 
      case ENOBUFS : 
      default : {
          break;
      }
    }  
#elif defined(__WINDOWS__)
    //do nothing
#endif
  }
  return result;
}

int32_t socketapi_recvex(int32_t socket, 
                         void* buffer, 
                         uint32_t length, 
                         uint32_t flag) {
  

  int32_t result = 0;
#if defined(__LINUX__)
  result = recv(socket, buffer, length, flag);
#elif defined(__WINDOWS__)
  result = recv(socket,(char*)buffer, length, flag);
#endif
  if (SOCKET_ERROR == result) {
#if defined(__LINUX__)
    switch (errno) {
      case EWOULDBLOCK : {
        result = kSocketErrorWouldBlock;
        break;
      }
      case ECONNRESET :
      case EPIPE :
      case EBADF : 
      case ENOTCONN : 
      case ENOTSOCK : 
      case EINTR : 
      case EFAULT : 

      default : {
        break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : { 
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTCONN : {
        strncpy(errormessage, "WSAENOTCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR : {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETRESET : {
        strncpy(errormessage, "WSAENETRESET", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEOPNOTSUPP : {
        strncpy(errormessage, "WSAEOPNOTSUPP", sizeof(errormessage) - 1);
        break;
      }
      case WSAESHUTDOWN : {
        strncpy(errormessage, "WSAESHUTDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEWOULDBLOCK : {
        //strncpy(errormessage, "WSAEWOULDBLOCK", sizeof(errormessage) - 1);
        result = kSocketErrorWouldBlock;
        break;
      }
      case WSAEMSGSIZE : {
        strncpy(errormessage, "WSAEMSGSIZE", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAECONNABORTED : {
        strncpy(errormessage, "WSAECONNABORTED", sizeof(errormessage) - 1);
        break;
      }
      case WSAETIMEDOUT : {
        strncpy(errormessage, "WSAETIMEDOUT", sizeof(errormessage) - 1);
        break;
      }
      case WSAECONNRESET : {
        strncpy(errormessage, "WSAECONNRESET", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
  } 
  else if (0 == result) {
    //do nothing
  }
  return result;
}

int32_t socketapi_recvfrom_ex(int32_t socket, 
                              void* buffer, 
                              int32_t length, 
                              uint32_t flag, 
                              struct sockaddr* from, 
                              uint32_t* fromlength) {
  
int32_t result = 0;
#if defined(__LINUX__)
  result = recvfrom(socket, buffer, length, flag, from, fromlength);
#elif defined(__WINDOWS__)
  result = 
    recvfrom(socket, (char*)buffer, length, flag, from, (int32_t*)fromlength);
#endif

  if (SOCKET_ERROR == result) {
#if defined(__LINUX__)
    switch (errno) {
      case EWOULDBLOCK : 
        result = kSocketErrorWouldBlock;
      case ECONNRESET :
      case EPIPE :
      case EBADF : 
      case ENOTCONN : 
      case ENOTSOCK : 
      case EINTR : 
      case EFAULT : 
      default : {
        break;
      }
    }
#elif defined(__WINDOWS__)
    //do nothing
#endif
  }
  return result;
}

bool socketapi_closesocket_ex(int32_t socket) {

  bool result = true;
#if defined(__LINUX__)
  fileapi_closeex(socket);
#elif defined(__WINDOWS__)
  if (SOCKET_ERROR == closesocket(socket)) {
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR : {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEWOULDBLOCK : {
        strncpy(errormessage, "WSAEWOULDBLOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
    result = false;
  }
#endif
  return result;
}


bool socketapi_ioctlsocket_ex(int32_t socket, int64_t cmd, uint64_t* argp) {
  bool result = true;
#if defined(__LINUX__)
  //do nothing
#elif defined(__WINDOWS__)
  if (SOCKET_ERROR == ioctlsocket(socket,(long)cmd,(u_long*)argp)) {
    int32_t error = WSAGetLastError();
      switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT : {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
    result = false;
  }
#endif
  return result;
} 

bool socketapi_get_nonblocking_ex(int32_t socketid) {
  bool result = true;
#if defined(__LINUX__)
  result = fileapi_get_nonblocking_ex(socketid);
#elif defined(__WINDOWS__)
  USE_PARAM(socketid);
  result = false;
#endif
  return result;
}

bool socketapi_set_nonblocking_ex(int32_t socket, bool on) {
  bool result = true;
#if defined(__LINUX__)
  fileapi_set_nonblocking_ex(socket, on);
#elif defined(__WINDOWS__)
  uint64_t argp = true == on ? 1 : 0;
  result = (bool)socketapi_ioctlsocket_ex(socket, FIONBIO, &argp);
#endif
  return result;
}

uint32_t socketapi_availableex(int32_t socket) {
  uint32_t result = 0;
#if defined(__LINUX__)
  result = fileapi_availableex(socket);
#elif defined(__WINDOWS__)
  uint64_t argp = 0;
  socketapi_ioctlsocket_ex(socket, FIONREAD, &argp);
  result = (uint32_t)argp;
#endif
  return result;
}

bool socketapi_shutdown_ex (int32_t socket, uint32_t how) {
  bool result = true;
  if (shutdown(socket,how) < 0) {
#if defined(__LINUX__)
    switch (errno) {
      case EBADF : 
      case ENOTSOCK : 
      case ENOTCONN : 
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN : {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL : {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS : {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTCONN : {
        strncpy(errormessage, "WSAENOTCONN", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK : {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
    result = false;
  }
  return result;
}

int32_t socketapi_selectex(int32_t maxfdp1, 
                           fd_set* readset, 
                           fd_set* writeset, 
                           fd_set* exceptset, 
                           struct timeval* timeout) {
  int32_t result = 0;
  result = select(maxfdp1, readset, writeset, exceptset, timeout);
  if(SOCKET_ERROR == result) {
#if defined(__LINUX__)

#elif defined(__WINDOWS__)
    int32_t error = WSAGetLastError();
    switch (error) {
      case WSANOTINITIALISED : {
        strncpy(errormessage, "WSANOTINITIALISED", sizeof(errormessage) - 1);
        break;
      }
      case WSAEFAULT: {
        strncpy(errormessage, "WSAEFAULT", sizeof(errormessage) - 1);
        break;
      }
      case WSAENETDOWN: {
        strncpy(errormessage, "WSAENETDOWN", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINVAL: {
        strncpy(errormessage, "WSAEINVAL", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINTR: {
        strncpy(errormessage, "WSAEINTR", sizeof(errormessage) - 1);
        break;
      }
      case WSAEINPROGRESS: {
        strncpy(errormessage, "WSAEINPROGRESS", sizeof(errormessage) - 1);
        break;
      }
      case WSAENOTSOCK: {
        strncpy(errormessage, "WSAENOTSOCK", sizeof(errormessage) - 1);
        break;
      }
      default : {
        strncpy(errormessage, "UNKNOWN", sizeof(errormessage) - 1);
        break;
      }
    }
#endif
  }
  return result;
}
