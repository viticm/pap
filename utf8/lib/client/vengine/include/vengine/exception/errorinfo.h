/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id errorinfo.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-17 12:02:16
 * @uses vengine exception error info functions
 */
#include "vengine/config.h"

namespace vengine_exception {

#pragma optimize("y", off)

namespace errorinfo {

bool create_smallinfo_dumpfile(PEXCEPTION_POINTERS exception, 
                               char* filename, 
                               uint16_t lasterror);
bool create_biginfo_dumpfile(PEXCEPTION_POINTERS exception,
                             char* filename,
                             uint16_t lasterror);
bool create_dumphelp_file(PEXCEPTION_POINTERS exception,
                          char* filename);
}; //namespce errorinfo

}; //namespace vengine_exception