#include "fileencode.h"

char get_base64char(int index) {
  const char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                     "jklmnopqrstuvwxyz0123456789+/";
  if ((index >= 0) && (index < 64)) {
    return str[index];
  }
  return '=';
}

void get_randomstr(char* buffer, int size) {
  int i, index;
  srand((unsigned int)time(NULL));
  for (i = 0; i < size; ++i) {
    index = rand() % 100;
    buffer[i] = get_base64char(index);
  }
}

int encode(const char* src_file, const char* dst_file) {
  //encode file build as: headflag + random head str + source encrypt str
  char head[ENCRYPT_POSITION - ENCRYPT_HEADFLAG_LEN + 1] = {0};
  char encrypt_head[ENCRYPT_POSITION - ENCRYPT_HEADFLAG_LEN + 1] = {0}; 
  FILE* fp1 = fopen(src_file, "rb");
  int result = -1;
  char* buff1 = NULL;
  char* buff2 = NULL;
  int filelen = 0;
  int size = 0;
  FILE* fp2 = NULL;
  if (1 == is_fileencode(src_file)) return -1;
  get_randomstr(head, sizeof(head) - 1);
  encrypt(head, encrypt_head, sizeof(encrypt_head) - 1);
  if (fp1) {
    fseek(fp1, 0, SEEK_END);
    filelen = ftell(fp1);
    buff1 = (char*)malloc(filelen);
    buff2 = (char*)malloc(filelen);
    if (buff1 && buff2) {
      fseek(fp1, 0, SEEK_SET);
      size = fread(buff1, 1, filelen, fp1);
      if (size <= 0) {
        return result;
      }
      encrypt(buff1, buff2, size);
      fp2 = fopen(dst_file, "wb");
      if (fp2) {
        fwrite(g_headflag, 1, ENCRYPT_HEADFLAG_LEN, fp2);
        fseek(fp2, ENCRYPT_HEADFLAG_LEN, SEEK_SET);
        fwrite(encrypt_head, 1, sizeof(encrypt_head) - 1, fp2);
        fseek(fp2, ENCRYPT_POSITION, SEEK_SET);
        fwrite(buff2, 1, size, fp2);
        fclose(fp2);
        result = 0;
      }
      fclose(fp1);
    }
  }
  SAFE_FREE(buff2);
  SAFE_FREE(buff1);
  return result;
}

int decode(const char* src_file, const char* dst_file) {
  FILE* fp1 = fopen(src_file, "rb");
  FILE* fp2 = NULL;
  int result = -1;
  char* buff1 = NULL;
  char* buff2 = NULL;
  int filelen = 0;
  int size = 0;

  if (0 == is_fileencode(src_file)) return -1;
  if (fp1) {
    fseek(fp1, 0, SEEK_END);
    filelen = ftell(fp1);
    buff1 = (char*)malloc(filelen - ENCRYPT_POSITION);
    buff2 = (char*)malloc(filelen - ENCRYPT_POSITION);
    if (buff1 && buff2) {
      fseek(fp1, ENCRYPT_POSITION, SEEK_SET);
      size = fread(buff1, 1, filelen, fp1);
      if (size <= 0) {
        return result;
      }
      encrypt(buff1, buff2, size);
      fp2 = fopen(dst_file, "wb");
      if (fp2) {
        fwrite(buff2, 1, size, fp2);
        fclose(fp2);
        result = 0;
      }
      fclose(fp1);
    }
  }
  SAFE_FREE(buff2);
  SAFE_FREE(buff1);
  return result;
}

void encrypt(const char* source, char* buffer, int size) {
  int i;
  for (i = 0; i < size; ++i) {
      buffer[i] = source[i] ^ 
          g_keytable[(i + ENCRYPT_POSITION) % ENCRYPT_OFFSET + ENCRYPT_STEP];
  }
}

int is_fileencode(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  int result = 0;
  char* headflag = NULL;
  int filelen;
  if (fp) {
    fseek(fp, 0, SEEK_END);
    filelen = ftell(fp);
    if (filelen < ENCRYPT_HEADFLAG_LEN) return 0;
    fseek(fp, 0, SEEK_SET);
    headflag = (char*)malloc(ENCRYPT_HEADFLAG_LEN);
    fread(headflag, 1, ENCRYPT_HEADFLAG_LEN, fp);
    if (0 == strcmp(headflag, g_headflag)) result = 1;
    fclose(fp);
  }
  SAFE_FREE(headflag);
  return result;
}

int main(int argc, char** argv) {
  int result = -1;
  int flag = 0;
  if (argc > 3) {
    if (0 == strcmp("-d", argv[1])) {
      flag = 0;
      result = decode(argv[2], argv[3]);
    }
    else if (0 == strcmp("-e", argv[1])) {
      flag = 1;
      result = encode(argv[2], argv[3]); 
    }
    printf("file %s %s: %s\n",
           argv[2],
           0 == flag ? "decode" : "encode", 
           0 == result ? "success": "failed");
  }
  return result;
}
