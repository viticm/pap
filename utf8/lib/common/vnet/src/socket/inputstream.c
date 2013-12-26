#include "socket/inputstream.h"
#include "socket/base.h"
#include "socket/endecode.h"

uint32_t socket_inputstream_encoderead(
    struct packet_t* packet, 
    char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  uint32_t result = length;
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
      if (packet.headlength < packet.taillength) {
        memcpy(tempbuffer, &((*packet).buffer[(*packet).headlength]), length);
      }
      else {
        uint32_t rightlength = (*packet).bufferlength - (*packet).headlength;
        if (length < rightlength) {
          memcpy(tempbuffer, &((*packet).buffer[packet.headlength]), length);
        }
        else {
          memcpy(tempbuffer, 
                 &((*packet).buffer[(*packet).headlength]),
                 rightlength);
          memcpy(&(tempbuffer[rightlength]), 
                 (*packet).buffer, 
                 length - rightlength);
        }
      }
      (*packet).headlength = 
        ((*packet).headlength + length) % (*packet).bufferlength;

      //decode it
      if ((*endecode_param).key != NULL && (*endecode_param).keysize > 0) {
        bool decoderesult = true;
        endecode_param->in = tempbuffer;
        endecode_param->insize = length;
        endecode_param->out = (unsigned char*)out; //change in make
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
  if (0 == length || length > socket_inputstream_reallength(*packet)) {
    result = 0;
  }
  else {
    if (packet.headlength < packet.taillength) {
      memcpy(buffer, &((*packet).buffer[(*packet).headlength]), length);
    }
    else {
      uint32_t rightlength = (*packet).bufferlength - (*packet).headlength;
      if (length < rightlength) {
        memcpy(buffer, &((*packet).buffer[packet.headlength]), length);
      }
      else {
        memcpy(buffer, &((*packet).buffer[packet.headlength]), rightlength);
        memcpy(&buffer[rightlength], (*packet).buffer, length - rightlength);
      }
    }
    (*packet).headlength = 
      ((*packet).headlength + length) % (*packet).bufferlength;
  }
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
    (*packet).headlength = 
      ((*packet).headlength + length) % (*packet).bufferlength;
  }
  return result;
}

int32_t socket_inputstream_fill(int32_t socketid, struct packet_t* packet) {
  int32_t fillcount = 0;
	int32_t receivecount = 0;
	int32_t freecount = 0;
	// head tail length=10
	// 0123456789
	// abcd......
  if ((*packet).headlength <= (*packet).taillength) {
    freecount = 0 == (*packet).headlength ? 
      (*packet).bufferlength - (*packet).taillength - 1 : 
      (*packet).bufferlength - (*packet).headlength;
  }
  else {
    freecount = (*packet).headlength - (*packet).taillength - 1;
  }

  if(freecount != 0) {
    receivecount = socketbase_receive(
        socketid, 
        &((*packet).buffer[(*packet).taillength]), 
        freecount, 
        0);
    if (kSocketErrorWouldBlock == receivecount) return 0; 
    if (SOCKET_ERROR == receivecount) return SOCKET_ERROR - 1;
    if (0 == receivecount) return SOCKET_ERROR - 2;
    (*packet).taillength += receivecount;
    fillcount += receivecount;
  }

  if (receivecount == freecount) {
    uint32_t available = socketbase_available(sockteid);
    if (available > 0) {
      if (((*packet).bufferlength + available + 1) > 
          (*packet).bufferlength_max) {
        return SOCKET_ERROR - 3;
      }
      if(!socket_inputstream_resize(packet, available + 1))
        return 0 ;
      receivecount = socketbase_receive(
        socketid, 
        &((*packet).buffer[(*packet).taillength]), 
        available, 
        0);
      if (kSocketErrorWouldBlock == receivecount) return 0; 
      if (SOCKET_ERROR == receivecount) return SOCKET_ERROR - 4;
      if (0 == receivecount) return SOCKET_ERROR - 5;

      (*packet).taillength += receivecount;
      fillcount += receivecount;
    }
  }
  return fillcount;
}

bool socket_inputstream_resize(packet_t* packet, int32_t size) {
  bool result = true;
  size = max(size, (int32_t)((*packet).bufferlength >> 1));
  uint32_t newbuffer_length = (*packet).bufferlength + size;
  uint32_t length = socket_inputstream_reallength(*packet);
  if (size < 0 && (newbuffer_length < 0 || newbuffer_length < length))
    return false;
  char* newbuffer = malloc(sizeof(char) * newbuffer_length);
  if ((*packet).headlength < (*packet).taillength) {
    memcpy(newbuffer, 
           &((*packet).buffer[(*packet).headlength]),
           (*packet).taillength - (*packet).headlength);
  }
  else if ((*packet).headlength >= (*packet).taillength) {
    memcpy(newbuffer, 
           &((*packet).buffer[(*packet).headlength]), 
           (*packe).bufferlength - (*packet).headlength);
    memcpy(&newbuffer[(*packet).bufferlength - (*packet).headlength], 
           (*packet).buffer, 
           (*packet).taillength);
  }
  SAFE_FREE(newbuffer);
  packet->buffer = newbuffer;
  packet->bufferlength = newbuffer_length;
  packet->headlength = 0;
  packet->taillength = length;
  return result;
}

bool socket_inputstream_skip(struct packet_t* packet, uint32_t length) {
  bool result = true;
  if (length < 0 || length > socket_inputstream_reallength(*packet))
    return false;
  packet->headlength = (packet->headlength + length) % packet->bufferlength;
  return result;
}
