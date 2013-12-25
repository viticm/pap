/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id api.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-25 9:44:03
 * @uses vnet file model api
 */

#include "base/config.h"

int32_t fileapi_openex(const char* filename, int32_t flag);
int32_t fileapi_openex(const char* filename, int32_t flag, int32_t mode);
void fileapi_closeex(int32_t fd);
uint32_t fileapi_readex(int32_t fd, void* buffer, uint32_t length);
uint32_t fileapi_writeex(int32_t fd, void* buffer, uint32_t length);
int32_t fileapi_fcntlex(int32_t fd, int32_t cmd);
int32_t fileapi_fcntlex(int32_t fd, int32_t cmd, int64_t arg);
bool fileapi_get_nonblocking_ex(int32_t fd);
bool fileapi_get_nonblocking_ex(int32_t fd, bool on);
void fileapi_ioctlex(int32_t fd, int32_t request, void* argp);
void fileapi_set_nonblocking_ex(int32_t fd, bool on);
void fileapi_availableex(int32_t fd);
int32_t fileapi_dupex(int32_t fd);
int64_t fileapi_lseekex(int32_t fd, int64_t offset, int32_t whence);
int64_t fileapi_tellex(int32_t fd);
