CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT (share_memory)

SET(TF_CURRENT_BINARY_PATH_BIN "../../../../run/server")
ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ADD_DEFINITIONS(-D_PAP_SHAREMEMORY)
ADD_DEFINITIONS(-D_USE_32BIT_TIME_T)

IF(CMAKE_SYSTEM MATCHES Linux)
  ADD_DEFINITIONS(-D__LINUX__)
  ADD_DEFINITIONS(-D_REENTRANT)
  ADD_DEFINITIONS(-DDONT_TD_VOID)
ELSE(CMAKE_SYSTEM MATCHES Linux)
  ADD_DEFINITIONS(-D__WINDOWS__)
ENDIF(CMAKE_SYSTEM MATCHES Linux)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
LINK_DIRECTORIES(
  "./" #run dir
  "../../../../lib/common/iconv/shared" #linux
  "../../../../lib/common/iconv/static" #win32
)

SET(EXECUTABLE_OUTPUT_PATH ${TF_CURRENT_BINARY_PATH_BIN})

##update_begin


INCLUDE_DIRECTORIES(../../../../include)


SET (SOURCEFILES_COMMON_BASE_LIST
	../../../common/base/md5.cc
	../../../common/base/string.cc
	../../../common/base/util.cc
)

SET (SOURCEFILES_COMMON_SYS_LIST
	../../../common/sys/assert.cc
	../../../common/sys/thread.cc
	../../../common/sys/util.cc
)

SET (SOURCEFILES_COMMON_FILE_LIST
	../../../common/file/ini.cc
)

SET (SOURCEFILES_COMMON_LIST
)

SET (SOURCEFILES_SERVER_COMMON_GAME_DB_LIST
	../../common/game/db/struct.cc
)

SET (SOURCEFILES_SERVER_COMMON_GAME_LIST
)

SET (SOURCEFILES_SERVER_COMMON_DB_DATA_LIST
	../../common/db/data/global.cc
	../../common/db/data/sql_template.cc
)

SET (SOURCEFILES_SERVER_COMMON_DB_LIST
	../../common/db/manager.cc
	../../common/db/odbc_interface.cc
	../../common/db/system.cc
)

SET (SOURCEFILES_SERVER_COMMON_BASE_LIST
	../../common/base/config.cc
	../../common/base/log.cc
	../../common/base/time_manager.cc
)

SET (SOURCEFILES_SERVER_COMMON_SYS_LIST
	../../common/sys/share_memory.cc
)

SET (SOURCEFILES_SERVER_COMMON_LIST
)

SET (SOURCEFILES_SERVER_SHAREMEMORY_SRC_MAIN_LIST
	../src/main/command_thread.cc
	../src/main/share_memory.cc
)

SET (SOURCEFILES_SERVER_SHAREMEMORY_SRC_DATA_LIST
	../src/data/logic_manager.cc
)

SET (SOURCEFILES_SERVER_SHAREMEMORY_SRC_LIST
)

SET (SOURCEFILES_SERVER_SHAREMEMORY_LIST
)

SET (SOURCEFILES_SERVER_LIST
)

SET (SOURCEFILES_LIST
)

SET (HEADERFILES_SERVER_COMMON_BASE_LIST
	../../../../include/server/common/base/config.h
	../../../../include/server/common/base/define.h
	../../../../include/server/common/base/file_define.h
	../../../../include/server/common/base/log.h
	../../../../include/server/common/base/log_define.h
	../../../../include/server/common/base/time_manager.h
)

SET (HEADERFILES_SERVER_COMMON_DB_DATA_LIST
	../../../../include/server/common/db/data/config.h
	../../../../include/server/common/db/data/global.h
	../../../../include/server/common/db/data/sql_template.h
)

SET (HEADERFILES_SERVER_COMMON_DB_LIST
	../../../../include/server/common/db/config.h
	../../../../include/server/common/db/manager.h
	../../../../include/server/common/db/odbc_interface.h
	../../../../include/server/common/db/system.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DB_LIST
	../../../../include/server/common/game/db/config.h
	../../../../include/server/common/game/db/define.h
	../../../../include/server/common/game/db/struct.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_LIST
	../../../../include/server/common/game/config.h
	../../../../include/server/common/game/define.h
	../../../../include/server/common/game/struct.h
)

SET (HEADERFILES_SERVER_COMMON_SYS_LIST
	../../../../include/server/common/sys/config.h
	../../../../include/server/common/sys/share_memory.h
)

SET (HEADERFILES_SERVER_COMMON_LIST
)

SET (HEADERFILES_SERVER_SHARE_MEMORY_MAIN_LIST
	../../../../include/server/share_memory/main/command_thread.h
	../../../../include/server/share_memory/main/share_memory.h
)

SET (HEADERFILES_SERVER_SHARE_MEMORY_DATA_LIST
	../../../../include/server/share_memory/data/config.h
	../../../../include/server/share_memory/data/logic_manager.h
)

SET (HEADERFILES_SERVER_SHARE_MEMORY_LIST
)

SET (HEADERFILES_SERVER_LIST
)

SET (HEADERFILES_COMMON_BASE_LIST
	../../../../include/common/base/config.h
	../../../../include/common/base/md5.h
	../../../../include/common/base/string.h
	../../../../include/common/base/type.h
	../../../../include/common/base/util.h
)

SET (HEADERFILES_COMMON_SYS_LIST
	../../../../include/common/sys/assert.h
	../../../../include/common/sys/config.h
	../../../../include/common/sys/thread.h
	../../../../include/common/sys/util.h
)

SET (HEADERFILES_COMMON_GAME_LIST
	../../../../include/common/game/config.h
	../../../../include/common/game/define.h
	../../../../include/common/game/struct.h
)

SET (HEADERFILES_COMMON_FILE_LIST
	../../../../include/common/file/config.h
	../../../../include/common/file/ini.h
)

SET (HEADERFILES_COMMON_LIST
)

SET (HEADERFILES_LIST
)

SET (RESOURCEFILES_LIST
)



if (WIN32)
	source_group(SourceFiles\\common\\base FILES ${SOURCEFILES_COMMON_BASE_LIST})
	source_group(SourceFiles\\common\\sys FILES ${SOURCEFILES_COMMON_SYS_LIST})
	source_group(SourceFiles\\common\\file FILES ${SOURCEFILES_COMMON_FILE_LIST})
	source_group(SourceFiles\\common FILES ${SOURCEFILES_COMMON_LIST})
	source_group(SourceFiles\\server\\common\\game\\db FILES ${SOURCEFILES_SERVER_COMMON_GAME_DB_LIST})
	source_group(SourceFiles\\server\\common\\game FILES ${SOURCEFILES_SERVER_COMMON_GAME_LIST})
	source_group(SourceFiles\\server\\common\\db\\data FILES ${SOURCEFILES_SERVER_COMMON_DB_DATA_LIST})
	source_group(SourceFiles\\server\\common\\db FILES ${SOURCEFILES_SERVER_COMMON_DB_LIST})
	source_group(SourceFiles\\server\\common\\base FILES ${SOURCEFILES_SERVER_COMMON_BASE_LIST})
	source_group(SourceFiles\\server\\common\\sys FILES ${SOURCEFILES_SERVER_COMMON_SYS_LIST})
	source_group(SourceFiles\\server\\common FILES ${SOURCEFILES_SERVER_COMMON_LIST})
	source_group(SourceFiles\\server\\sharememory\\src\\main FILES ${SOURCEFILES_SERVER_SHAREMEMORY_SRC_MAIN_LIST})
	source_group(SourceFiles\\server\\sharememory\\src\\data FILES ${SOURCEFILES_SERVER_SHAREMEMORY_SRC_DATA_LIST})
	source_group(SourceFiles\\server\\sharememory\\src FILES ${SOURCEFILES_SERVER_SHAREMEMORY_SRC_LIST})
	source_group(SourceFiles\\server\\sharememory FILES ${SOURCEFILES_SERVER_SHAREMEMORY_LIST})
	source_group(SourceFiles\\server FILES ${SOURCEFILES_SERVER_LIST})
	source_group(SourceFiles FILES ${SOURCEFILES_LIST})
	source_group(HeaderFiles\\server\\common\\base FILES ${HEADERFILES_SERVER_COMMON_BASE_LIST})
	source_group(HeaderFiles\\server\\common\\db\\data FILES ${HEADERFILES_SERVER_COMMON_DB_DATA_LIST})
	source_group(HeaderFiles\\server\\common\\db FILES ${HEADERFILES_SERVER_COMMON_DB_LIST})
	source_group(HeaderFiles\\server\\common\\game\\db FILES ${HEADERFILES_SERVER_COMMON_GAME_DB_LIST})
	source_group(HeaderFiles\\server\\common\\game FILES ${HEADERFILES_SERVER_COMMON_GAME_LIST})
	source_group(HeaderFiles\\server\\common\\sys FILES ${HEADERFILES_SERVER_COMMON_SYS_LIST})
	source_group(HeaderFiles\\server\\common FILES ${HEADERFILES_SERVER_COMMON_LIST})
	source_group(HeaderFiles\\server\\share\\memory\\main FILES ${HEADERFILES_SERVER_SHARE_MEMORY_MAIN_LIST})
	source_group(HeaderFiles\\server\\share\\memory\\data FILES ${HEADERFILES_SERVER_SHARE_MEMORY_DATA_LIST})
	source_group(HeaderFiles\\server\\share\\memory FILES ${HEADERFILES_SERVER_SHARE_MEMORY_LIST})
	source_group(HeaderFiles\\server FILES ${HEADERFILES_SERVER_LIST})
	source_group(HeaderFiles\\common\\base FILES ${HEADERFILES_COMMON_BASE_LIST})
	source_group(HeaderFiles\\common\\sys FILES ${HEADERFILES_COMMON_SYS_LIST})
	source_group(HeaderFiles\\common\\game FILES ${HEADERFILES_COMMON_GAME_LIST})
	source_group(HeaderFiles\\common\\file FILES ${HEADERFILES_COMMON_FILE_LIST})
	source_group(HeaderFiles\\common FILES ${HEADERFILES_COMMON_LIST})
	source_group(HeaderFiles FILES ${HEADERFILES_LIST})
	source_group(ResourceFiles FILES ${RESOURCEFILES_LIST})
endif()


ADD_EXECUTABLE(share_memory
	${SOURCEFILES_COMMON_BASE_LIST}
	${SOURCEFILES_COMMON_SYS_LIST}
	${SOURCEFILES_COMMON_FILE_LIST}
	${SOURCEFILES_COMMON_LIST}
	${SOURCEFILES_SERVER_COMMON_GAME_DB_LIST}
	${SOURCEFILES_SERVER_COMMON_GAME_LIST}
	${SOURCEFILES_SERVER_COMMON_DB_DATA_LIST}
	${SOURCEFILES_SERVER_COMMON_DB_LIST}
	${SOURCEFILES_SERVER_COMMON_BASE_LIST}
	${SOURCEFILES_SERVER_COMMON_SYS_LIST}
	${SOURCEFILES_SERVER_COMMON_LIST}
	${SOURCEFILES_SERVER_SHAREMEMORY_SRC_MAIN_LIST}
	${SOURCEFILES_SERVER_SHAREMEMORY_SRC_DATA_LIST}
	${SOURCEFILES_SERVER_SHAREMEMORY_SRC_LIST}
	${SOURCEFILES_SERVER_SHAREMEMORY_LIST}
	${SOURCEFILES_SERVER_LIST}
	${SOURCEFILES_LIST}
	${HEADERFILES_SERVER_COMMON_BASE_LIST}
	${HEADERFILES_SERVER_COMMON_DB_DATA_LIST}
	${HEADERFILES_SERVER_COMMON_DB_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DB_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_LIST}
	${HEADERFILES_SERVER_COMMON_SYS_LIST}
	${HEADERFILES_SERVER_COMMON_LIST}
	${HEADERFILES_SERVER_SHARE_MEMORY_MAIN_LIST}
	${HEADERFILES_SERVER_SHARE_MEMORY_DATA_LIST}
	${HEADERFILES_SERVER_SHARE_MEMORY_LIST}
	${HEADERFILES_SERVER_LIST}
	${HEADERFILES_COMMON_BASE_LIST}
	${HEADERFILES_COMMON_SYS_LIST}
	${HEADERFILES_COMMON_GAME_LIST}
	${HEADERFILES_COMMON_FILE_LIST}
	${HEADERFILES_COMMON_LIST}
	${HEADERFILES_LIST}
	${RESOURCEFILES_LIST}
)


##update_end

if(USE_32BITS)
  SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
  SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
else()
  SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
  SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
endif(USE_32BITS)

if (WIN32)
TARGET_LINK_LIBRARIES(share_memory ws2_32.lib odbc32.lib odbccp32.lib iconv.h)
else()
TARGET_LINK_LIBRARIES(share_memory pthread odbc iconv)
  if(USE_32BITS)
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
  else()
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
  endif(USE_32BITS)
endif(WIN32)
