#include "file/api.h"

#if defined(__LINUX__) /* { */
#include <sys/types.h>  // for open()
#include <sys/stat.h>   // for open()
#include <unistd.h>     // for fcntl()
#include <fcntl.h>      // for fcntl()
#include <sys/ioctl.h>  // for ioctl()
#include <errno.h>      // for errno
#elif defined(__WINDOWS__) /* { */
#include <io.h>         // for _open()
#include <fcntl.h>      // for _open()/_close()/_read()/_write()...
#endif /* } */

#if defined(__LINUX__)
extern int32_t errno;
#endif

int32_t fileapi_openex(const char* filename, int32_t flag) {
#if defined(__LINUX__)
  int32_t fd = open(filename, flag);
#elif defined(__WINDOWS__)
  int32_t fd = _open(filename, flag);
#endif
  if (fd < 0) {
#if defined(__LINUX__)
    switch (errno) {
      case EEXIST : 
      case ENOENT : 
      case EISDIR : 
      case EACCES : 
      case ENAMETOOLONG : 
      case ENOTDIR : 
      case ENXIO : 
      case ENODEV : 
      case EROFS : 
      case ETXTBSY : 
      case EFAULT : 
      case ELOOP : 
      case ENOSPC : 
      case ENOMEM : 
      case EMFILE : 
      case ENFILE : 
      default : {
        break;
      }
    }//end of switch
#elif defined(__WINDOWS__)
  // ...
#endif
  }
  return fd;
}

int32_t fileapi_openex (const char * filename, int32_t flag, int32_t mode) {
#if defined(__LINUX__)
  int32_t fd = open(filename, flag, mode);
#elif defined(__WINDOWS__)
  int32_t fd = _open(filename, flag, mode);
#endif

  if (fd < 0) {
#if defined(__LINUX__)
    switch (errno) {
      case EEXIST : 
      case EISDIR : 
      case EACCES : 
      case ENAMETOOLONG : 
      case ENOENT : 
      case ENOTDIR : 
      case ENXIO : 
      case ENODEV : 
      case EROFS : 
      case ETXTBSY : 
      case EFAULT : 
      case ELOOP : 
      case ENOSPC : 
      case ENOMEM : 
      case EMFILE : 
      case ENFILE : 
      default : {
        break;
      }
    }//end of switch
#elif defined(__WINDOWS__)
  // ...
#endif
  }
  return fd;
}


uint32_t fileapi_readex(int32_t fd, void* buffer, uint32_t length) {
#if defined(__LINUX__)
  int32_t result = read(fd, buffer, length);
#elif defined(__WINDOWS__)
  int32_t result = _read (fd, buffer, length);
#endif
  if (result < 0) {

#if defined(__LINUX__)
    switch (errno) {
      case EINTR : 
      case EAGAIN : 
      case EBADF : 
      case EIO : 
      case EISDIR : 
      case EINVAL : 
      case EFAULT : 
      case ECONNRESET :
      default : {
        break;
      }
    }
#elif defined(__WINDOWS__)
  // ...
#endif
  } 
  else if (0 == result) {

  }
  return result;
}

uint32_t fileapi_writeex(int32_t fd, const void* buffer, uint32_t length) {
#if defined(__LINUX__)
  int32_t result = write(fd, buffer, length);
#elif defined(__WINDOWS__)
  int32_t result = _write(fd, buffer, length);
#endif

  if (result < 0) {
    
#if defined(__LINUX__)
    switch (errno) {
      case EAGAIN : 
      case EINTR : 
      case EBADF : 
      case EPIPE : 
      case EINVAL: 
      case EFAULT: 
      case ENOSPC : 
      case EIO : 
      case ECONNRESET :
      default : {
          break;
      }
    }
#elif __WINDOWS__
  //...
#endif
  }
  return result;
}


void fileapi_closeex(int32_t fd) {
  if (close(fd) < 0) {
#if defined(__LINUX__)
    switch ( errno ) {
      case EBADF : 
      default : {
          break;
      }
    }
#elif defined(__WINDOWS__)
//do nothing
#endif
  }
}

int32_t fileapi_fcntlex(int32_t fd, int32_t cmd) {
#if defined(__LINUX__)
  int32_t result = fcntl(fd, cmd);
  if (result < 0) {
    switch (errno) {
      case EINTR : 
      case EBADF : 
      case EACCES : 
      case EAGAIN : 
      case EDEADLK : 
      case EMFILE : 
      case ENOLCK : 
      default : {
        break;
      }
    }
  }
  return result;
#elif defined(__WINDOWS__)
  return 0 ;
#endif
}

int32_t fileapi_fcntlex(int32_t fd, int32_t cmd, int32_t arg) {
#if defined(__LINUX__)
  int32_t result = fcntl(fd, cmd, arg);
  if (result < 0) {
    switch (errno) {
      case EINTR : 
      case EINVAL : 
      case EBADF : 
      case EACCES : 
      case EAGAIN : 
      case EDEADLK : 
      case EMFILE : 
      case ENOLCK : 
      default : {
        break;
      }
    }
  }
  return result;
#elif defined(__WINDOWS__)
  return 0 ;
#endif
}

bool fileapi_get_nonblocking_ex(int32_t fd) {
#if defined(__LINUX__)
  int32_t flag = fileapi_fcntlex(fd, F_GETFL, 0);
  return flag | O_NONBLOCK;
#elif defined(__WINDOWS__)
  return false;
#endif
}

void fileapi_set_nonblocking_ex (int32_t fd, bool on) {
#if defined(__LINUX__)
  int32_t flag = fileapi_fcntlex(fd, F_GETFL, 0);
  if (on)
    // make nonblocking fd
    flag |= O_NONBLOCK;
  else
    // make blocking fd
    flag &= ~O_NONBLOCK;
  fileapi_fcntlex(fd, F_SETFL, flag);
#elif defined(__WINDOWS__)
  //do nothing
#endif
}

void fileapi_ioctlex (int32_t fd, int32_t request, void* argp) {
#if defined(__LINUX__)
  if (ioctl(fd,request,argp) < 0) {
    switch (errno) {
      case EBADF : 
      case ENOTTY : 
      case EINVAL : 
      default :
      {
        break;
      }
    }
  }
#elif defined(__WINDOWS__)
  //do nothing
#endif
}



void fileapi_setnonblocking_ex(int32_t fd, bool on) {
#if defined(__LINUX__)
  uint64_t arg = (true == on ? 1 : 0 );
  fileapi_ioctlex(fd, FIONBIO, &arg);
#elif defined(__WINDOWS__)
  //do nothing
#endif
}


uint32_t fileapi_availableex(int32_t fd) {
#if defined(__LINUX__)
  uint32_t arg = 0;
  fileaip_ioctlex(fd, FIONREAD, &arg);
  return arg;
#elif defined(__WINDOWS__)
  return 0;
#endif
}


int32_t fileapi_dupex(int32_t fd) {
#if defined(__LINUX__)
  int32_t newfd = dup(fd);
#elif defined(__WINDOWS__)
  int32_t newfd = _dup(fd);
#endif

  if (newfd < 0) {
#if defined(__LINUX__)
    switch (errno) {
      case EBADF : 
      case EMFILE : 
      default : {
        break;
      }
    }
#elif defined(__WINDOWS__)
    //do nothing
#endif
  }
  return newfd;
}


int64_t fileapi_lseekex(int32_t fd, uint64_t offset, int32_t whence) {
#if defined(__LINUX__)
  int64_t result = lseek(fd, offset, whence);
  if (result < 0) {
    switch (errno) {
      case EBADF : 
      case ESPIPE : 
      case EINVAL : 
      default : {
        break;
      }
    }
  }
#elif __WINDOWS__
  uint64_t result = _lseek(fd, offset, whence);
  if ( result < 0 ) {
  }
#endif
  return result;
}

int64_t fileapi_tellex(int32_t fd) {
#if defined(__LINUX__)
  int64_t result;
#elif defined(__WINDOWS__)
  int64_t result = _tell(fd);
  if (result < 0) {
  }
#endif
  return result ;
}
