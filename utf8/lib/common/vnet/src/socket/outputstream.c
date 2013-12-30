#include "socket/outputstream.h"
#include "socket/base.h"
#include "socket/endecode.h"

uint32_t socket_outputstream_write(struct packet_t* packet, 
                                   const char* buffer, 
                                   uint32_t length) {
  uint32_t result = length;
  /**
   * tail head       head tail --length 10
   * 0123456789      0123456789
   * abcd...efg      ...abcd...
   */
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t freecount = headlength <= taillength ? 
    bufferlength - taillength + headlength - 1 :
    headlength - taillength - 1;
  if (length >= freecount && 
      !socket_outputstream_resize(packet, length - freecount + 1)) {
    result = 0;  
  }
  else {
    if (headlength <= taillength && 
        taillength != 0 && 
        (freecount = bufferlength - taillength) <= length) {
      memcpy(&(packet->buffer[taillength]), buffer, freecount);
      memcpy(packet->buffer, &buffer[freecount], length - freecount);
    }
    else {
      memcpy(&(packet->buffer[taillength]), buffer, length);
    }
    packet->taillength = (taillength + length) % bufferlength;
  }
  return result;
}
uint32_t socket_outputstream_encodewrite(
    struct packet_t* packet, 
    const char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  uint32_t result = length;
  bool endecoderesult = true;
  /**
   * tail head       head tail --length 10
   * 0123456789      0123456789
   * abcd...efg      ...abcd...
   */
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t freecount = headlength <= taillength ? 
    bufferlength - taillength + headlength - 1 :
    headlength - taillength - 1;
  if (length >= freecount && 
      !socket_outputstream_resize(packet, length - freecount + 1)) {
    result = 0;  
  }
  else {
    unsigned char* tempbuffer = (unsigned char*)malloc(sizeof(unsigned char) * length);
    if (NULL == tempbuffer) return 0; //memory failed
    if ((*endecode_param).key != NULL && (*endecode_param).keysize > 0) {
      endecode_param->in = (unsigned char*)buffer;
      endecode_param->insize = length;
      endecode_param->out = tempbuffer;
      endecode_param->outsize = length;
      endecoderesult = socketendecode_make(endecode_param);
      if (false == endecoderesult) { //endecode failed
        SAFE_FREE(tempbuffer);
        return 0;
      }
    }
    else { //can't endecode
      memcpy(tempbuffer, buffer, length);
    }

    if (headlength <= taillength && 
        taillength != 0 && 
        (freecount = bufferlength - taillength) <= length) {
      memcpy(&(packet->buffer[taillength]), tempbuffer, freecount);
      memcpy(packet->buffer, &tempbuffer[freecount], length - freecount);
    }
    else {
      memcpy(&(packet->buffer[taillength]), tempbuffer, length);
    }
    SAFE_FREE(tempbuffer);
    packet->taillength = (taillength + length) % bufferlength;
  }
  return result;

}
uint32_t socket_outputstream_reallength(struct packet_t packet) {
  uint32_t result = 0;
  if (packet.headlength < packet.taillength) {
    result = packet.taillength - packet.headlength;
  }
  else if (packet.headlength > packet.taillength) {
    result = packet.bufferlength - packet.headlength + packet.taillength;
  }
  return result;
}

int32_t socket_outputstream_flush(int32_t socketid, struct packet_t* packet) {
  uint32_t flushcount = 0;
  uint32_t sendcount = 0;
  uint32_t leftcount = 0;
  uint32_t flag = 0;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t bufferlength_max = (*packet).bufferlength_max;
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  char* buffer = (char*)malloc(bufferlength);
  memcpy(buffer, (*packet).buffer, bufferlength);
  if (bufferlength > bufferlength_max) {
    socket_outputstream_packetinit(packet);   
    return SOCKET_ERROR - 1;
  }
#if defined(__LINUX__)
  flag = MSG_NOSIGNAL;
#elif defined(__WINDOWS__)
  flag = MSG_DONTROUTE;
#endif
  leftcount = headlength < taillength ? taillength - headlength :
    bufferlength - headlength;
  while (leftcount > 0) {
    sendcount = socketbase_send(socketid, &buffer[headlength], leftcount, flag);
    if (SOCKET_ERROR_WOULD_BLOCK == sendcount) {
      SAFE_FREE(buffer);
      return 0;
    }
    if (SOCKET_ERROR == sendcount) {
      SAFE_FREE(buffer);
      return SOCKET_ERROR - 2;
    }
    if (0 == sendcount) {
      SAFE_FREE(buffer);
      return 0;
    }
    flushcount += sendcount;
    leftcount -= sendcount;
    packet->headlength += sendcount;
  }

  if (headlength > taillength) {
    packet->headlength = 0;
    leftcount = taillength;
    while (leftcount > 0) {
      sendcount = socketbase_send(socketid, &buffer[headlength], leftcount, flag);
      if (SOCKET_ERROR_WOULD_BLOCK == sendcount) {
        SAFE_FREE(buffer);
        return 0;
      }
      if (SOCKET_ERROR == sendcount) {
        SAFE_FREE(buffer);
        return SOCKET_ERROR - 3;
      }
      if (0 == sendcount) {
        SAFE_FREE(buffer);
        return 0;
      }
      flushcount += sendcount;
      leftcount -= sendcount;
      packet->headlength += sendcount;
    }
  }
  packet->headlength = packet->taillength = 0;
  SAFE_FREE(buffer);
  return flushcount;
}

bool socket_outputstream_resize(struct packet_t* packet, int32_t size) {
  bool result = true;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  uint32_t newbuffer_length = 0;
  uint32_t length =  0;
  char* buffer = (*packet).buffer;
  char* newbuffer = NULL;
  size = max(size, (int32_t)(bufferlength >> 1));
  newbuffer_length = bufferlength + size;
  length = socket_outputstream_reallength(*packet);
  if (size < 0 && (newbuffer_length < 0 || newbuffer_length < length))
    return false;
  newbuffer = (char*)malloc(newbuffer_length);
  if (headlength < taillength) {
    memcpy(newbuffer, &buffer[headlength], taillength - headlength);
  }
  else if (headlength >= taillength) {
    memcpy(newbuffer, &buffer[headlength], bufferlength - headlength);
    memcpy(&newbuffer[bufferlength - headlength], buffer, taillength);
  }
  SAFE_FREE(newbuffer);
  packet->buffer = newbuffer;
  packet->bufferlength = newbuffer_length;
  packet->headlength = 0;
  packet->taillength = length;
  return result;
}

void socket_outputstream_packetinit(struct packet_t* packet) {
  packet->headlength = 0;
  packet->taillength = 0;
  SAFE_FREE(packet->buffer);
  packet->bufferlength = SOCKETOUTPUT_BUFFERSIZE_DEFAULT;
  packet->bufferlength_max = SOCKETOUTPUT_DISCONNECT_MAXSIZE;
  packet->buffer = (char*)malloc(sizeof(char) * (*packet).bufferlength);
  memset(packet->buffer, '\0', sizeof(char) * (*packet).bufferlength);
}
