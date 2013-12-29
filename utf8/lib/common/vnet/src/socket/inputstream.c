#include "socket/inputstream.h"
#include "socket/base.h"
#include "socket/endecode.h"

uint32_t socket_inputstream_encoderead(
    struct packet_t* packet, 
    char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  uint32_t result = length;
  char* packetbuffer = (*packet).buffer;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  if (0 == length || length > socket_inputstream_reallength(*packet)) {
    result = 0;
  }
  else {
    unsigned char* tempbuffer;
    tempbuffer = (unsigned char*)malloc(sizeof(unsigned char) * length);
    if (NULL == tempbuffer) {
      result = 0;
    }
    else {
      if (headlength < taillength) {
        memcpy(tempbuffer, &buffer[headlength], length);
      }
      else {
        uint32_t rightlength = bufferlength - headlength;
        if (length < rightlength) {
          memcpy(tempbuffer, &packetbuffer[headlength], length);
        }
        else {
          memcpy(tempbuffer, &packetbuffer[headlength], rightlength);
          memcpy(&(tempbuffer[rightlength]), 
                 packetbuffer, 
                 length - rightlength);
        }
      }
      packet->headlength = (headlength + length) % bufferlength;

      //decode it
      if ((*endecode_param).key != NULL && (*endecode_param).keysize > 0) {
        bool decoderesult = true;
        endecode_param->in = tempbuffer;
        endecode_param->insize = length;
        endecode_param->out = (unsigned char*)buffer; //change in make
        endecode_param->outsize = length;
        decoderesult = socketendecode_make(endecode_param);
        if (false == decoderesult) length = 0;
      }
      else {
        memcpy(buffer, tempbuffer, length);
      }
      SAFE_FREE(tempbuffer);
    }
  }
  return result;
}

uint32_t socket_inputstream_read(struct packet_t* packet, 
                                 char* buffer, 
                                 uint32_t length) {
  uint32_t result = length;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  char* packetbuffer = (char*)malloc(bufferlength);
  memcpy(packetbuffer, (*packet).buffer, bufferlength);
  if (0 == length || length > socket_inputstream_reallength(*packet)) {
    result = 0;
  }
  else {
    if (headlength < taillength) {
      memcpy(buffer, &packetbuffer[headlength], length);
    }
    else {
      uint32_t rightlength = bufferlength - headlength;
      if (length < rightlength) {
        memcpy(buffer, &packetbuffer[headlength], length);
      }
      else {
        memcpy(buffer, &packetbuffer[headlength], rightlength);
        memcpy(&buffer[rightlength], packetbuffer, length - rightlength);
      }
    }
    packet->headlength = headlength + length % bufferlength;
  }
  SAFE_FREE(packetbuffer);
  return result;
}


uint32_t socket_inputstream_reallength(struct packet_t packet) {
  uint32_t result = 0;
  if (packet.headlength < packet.taillength) {
    result = packet.taillength - packet.headlength;
  }
  else if (packet.headlength > packet.taillength) {
    result = packet.bufferlength - packet.headlength + packet.taillength;
  }
  return result;
}

bool socket_inputstream_peek(struct packet_t packet,
                             char* buffer,
                             uint32_t length) {
  bool result = true;
  if (0 == length || length > socket_inputstream_reallength(packet)) {
    result = false;
  }
  else {
    if (packet.headlength < packet.taillength) {
      memcpy(buffer, &packet.buffer[packet.headlength], length);
    }
    else {
      uint32_t rightlength = packet.bufferlength - packet.headlength;
      if (length < rightlength) {
        memcpy(&buffer[0], &packet.buffer[packet.headlength], length);
      }
      else {
        memcpy(&buffer[0], &packet.buffer[packet.headlength], rightlength);
        memcpy(&buffer[rightlength], &packet.buffer[0], length - rightlength);
      }
    }
  }
  return result;
}

bool socket_inputstream_skip(struct packet_t* packet, uint32_t length) {
  bool result = true;
  if (0 == length || length > socket_inputstream_reallength(*packet)) {
    result = false;
  }
  else {
    uint32_t headlength  = (*packet).headlength;
    uint32_t bufferlength = (*packet).bufferlength;
    packet->headlength = (headlength + length) % bufferlength;
  }
  return result;
}

int32_t socket_inputstream_fill(int32_t socketid, struct packet_t* packet) {
  int32_t fillcount = 0;
	int32_t receivecount = 0;
	uint32_t freecount = 0;
  uint32_t bufferlength = (*packet).bufferlength;
  uint32_t bufferlength_max = (*packet).bufferlength_max;
  uint32_t headlength = (*packet).headlength;
  uint32_t taillength = (*packet).taillength;
  char* buffer = (char*)malloc(bufferlength);
  memset(buffer, '\0', bufferlength);
  memcpy(buffer, (*packet).buffer, bufferlength);
	// head tail length=10
	// 0123456789
	// abcd......
  if (headlength <= taillength) {
    freecount = 0 == headlength ? 
      bufferlength - taillength - 1 : 
      bufferlength - headlength;
  }
  else {
    freecount = headlength - taillength - 1;
  }

  if(freecount != 0) {
    receivecount = socketbase_receive(socketid, 
                                      &buffer[taillength], 
                                      freecount, 
                                      0);
    if (kSocketErrorWouldBlock == receivecount) {
      SAFE_FREE(buffer);
      return 0;
    }
    if (SOCKET_ERROR == receivecount) {
      SAFE_FREE(buffer);
      return SOCKET_ERROR - 1;
    }
    if (0 == receivecount) {
      SAFE_FREE(buffer);
      return SOCKET_ERROR - 2;
    }
    packet->taillength += receivecount;
    fillcount += receivecount;
  }

  if (receivecount == (int32_t)freecount) {
    uint32_t available = socketbase_available(socketid);
    if (available > 0) {
      if ((bufferlength + available + 1) > 
          bufferlength_max) {
        socket_inputstream_packetinit(packet); //reset packet
        SAFE_FREE(buffer);
        return SOCKET_ERROR - 3;
      }
      if(!socket_inputstream_resize(packet, available + 1))
        return 0 ;
      receivecount = socketbase_receive(socketid, 
                                        &buffer[taillength], 
                                        available, 
                                        0);
      if (kSocketErrorWouldBlock == receivecount) {
        SAFE_FREE(buffer);
        return 0;
      }
      if (SOCKET_ERROR == receivecount) {
        SAFE_FREE(buffer);
        return SOCKET_ERROR - 4;
      }
      if (0 == receivecount) {
        SAFE_FREE(buffer);
        return SOCKET_ERROR - 5;
      }

      packet->taillength += receivecount;
      fillcount += receivecount;
    }
  }
  SAFE_FREE(buffer);
  return fillcount;
}

bool socket_inputstream_resize(struct packet_t* packet, int32_t size) {
  bool result = true;
  uint32_t bufferlength = 0;
  uint32_t headlength = 0;
  uint32_t taillength = 0;
  uint32_t newbuffer_length = 0;
  uint32_t length = 0;
  char* buffer = NULL;
  char* newbuffer = NULL;
  bufferlength = (*packet).bufferlength;
  headlength = (*packet).headlength;
  taillength = (*packet).taillength;
  newbuffer_length = bufferlength + size;
  length = socket_inputstream_reallength(*packet);
  buffer = (char*)malloc(bufferlength);
  size = max(size, (int32_t)((*packet).bufferlength >> 1));
  memset(buffer, '\0', bufferlength);
  memcpy(buffer, (*packet).buffer, bufferlength);
  if (size < 0 && (newbuffer_length < 0 || newbuffer_length < length))
    return false;
  newbuffer = (char*)malloc(sizeof(char) * newbuffer_length);
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

void socket_inputstream_packetinit(struct packet_t* packet) {
  packet->headlength = 0;
  packet->taillength = 0;
  SAFE_FREE(packet->buffer);
  packet->bufferlength = SOCKETINPUT_BUFFERSIZE_DEFAULT;
  packet->bufferlength_max = SOCKETINPUT_DISCONNECT_MAXSIZE;
  packet->buffer = (char*)malloc((*packet).bufferlength);
  memset(packet->buffer, '\0', (*packet).bufferlength);
}
