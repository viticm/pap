CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT (billing)

SET(TF_CURRENT_BINARY_PATH_BIN "../../../../run/server")
ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ADD_DEFINITIONS(-D_PAP_BILLING)
ADD_DEFINITIONS(-D_PAP_NET_BILLING)
ADD_DEFINITIONS(-DUTF8)
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
  "../../../../lib/common/iconv/link" #linux
  "../../../../lib/common/vnet/link" #win32
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
	../../../common/sys/minidump.cc
	../../../common/sys/thread.cc
	../../../common/sys/util.cc
)

SET (SOURCEFILES_COMMON_FILE_LIST
	../../../common/file/database.cc
	../../../common/file/ini.cc
)

SET (SOURCEFILES_COMMON_NET_PACKET_LIST
	../../../common/net/packet/base.cc
	../../../common/net/packet/factorymanager.cc
)

SET (SOURCEFILES_COMMON_NET_SOCKET_LIST
	../../../common/net/socket/base.cc
	../../../common/net/socket/inputstream.cc
	../../../common/net/socket/outputstream.cc
)

SET (SOURCEFILES_COMMON_NET_LIST
)

SET (SOURCEFILES_COMMON_LIST
)

SET (SOURCEFILES_SERVER_COMMON_GAME_LIST
)

SET (SOURCEFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST
	../../common/net/packets/billing_tologin/resultauth.cc
)

SET (SOURCEFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST
	../../common/net/packets/login_tobilling/askauth.cc
)

SET (SOURCEFILES_SERVER_COMMON_NET_PACKETS_LIST
)

SET (SOURCEFILES_SERVER_COMMON_NET_CONNECTION_LIST
	../../common/net/connection/base.cc
	../../common/net/connection/manager.cc
	../../common/net/connection/server.cc
)

SET (SOURCEFILES_SERVER_COMMON_NET_LIST
	../../common/net/socket.cc
)

SET (SOURCEFILES_SERVER_COMMON_BASE_LIST
	../../../common/base/io.cc
	../../common/base/config.cc
	../../common/base/log.cc
	../../common/base/time_manager.cc
)

SET (SOURCEFILES_SERVER_COMMON_SYS_LIST
)

SET (SOURCEFILES_SERVER_COMMON_LIST
)

SET (SOURCEFILES_SERVER_BILLING_SRC_MAIN_LIST
	../src/main/accounttable.cc
	../src/main/billing.cc
	../src/main/servermanager.cc
)

SET (SOURCEFILES_SERVER_BILLING_SRC_CONNECTION_LIST
	../src/connection/billing.cc
	../src/connection/manager.cc
	../src/connection/pool.cc
	../src/connection/server.cc
)

SET (SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_BILLING_TOLOGIN_LIST
	../src/packets/handler/billing_tologin/resultauth.cc
)

SET (SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LOGIN_TOBILLING_LIST
	../src/packets/handler/login_tobilling/askauth.cc
)

SET (SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LIST
)

SET (SOURCEFILES_SERVER_BILLING_SRC_PACKETS_LIST
)

SET (SOURCEFILES_SERVER_BILLING_SRC_LIST
)

SET (SOURCEFILES_SERVER_BILLING_LIST
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

SET (HEADERFILES_SERVER_COMMON_NET_CONNECTION_LIST
	../../../../include/server/common/net/connection/base.h
	../../../../include/server/common/net/connection/manager.h
	../../../../include/server/common/net/connection/server.h
)

SET (HEADERFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST
	../../../../include/server/common/net/packets/billing_tologin/resultauth.h
)

SET (HEADERFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST
	../../../../include/server/common/net/packets/login_tobilling/askauth.h
)

SET (HEADERFILES_SERVER_COMMON_NET_PACKETS_LIST
)

SET (HEADERFILES_SERVER_COMMON_NET_LIST
	../../../../include/server/common/net/config.h
	../../../../include/server/common/net/socket.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_TYPE_LIST
	../../../../include/server/common/game/define/type/all.h
	../../../../include/server/common/game/define/type/server.h
	../../../../include/server/common/game/define/type/sharememory.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_PACKET_LIST
	../../../../include/server/common/game/define/id/packet/all.h
	../../../../include/server/common/game/define/id/packet/billinglogin.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_LIST
	../../../../include/server/common/game/define/id/all.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_STATUS_LIST
	../../../../include/server/common/game/define/status/all.h
	../../../../include/server/common/game/define/status/connection.h
	../../../../include/server/common/game/define/status/sharememory.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_RESULT_LIST
	../../../../include/server/common/game/define/result/all.h
	../../../../include/server/common/game/define/result/userdata.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_DEFINE_LIST
	../../../../include/server/common/game/define/all.h
	../../../../include/server/common/game/define/enum.h
	../../../../include/server/common/game/define/macros.h
)

SET (HEADERFILES_SERVER_COMMON_GAME_LIST
)

SET (HEADERFILES_SERVER_COMMON_SYS_LIST
	../../../../include/server/common/sys/config.h
)

SET (HEADERFILES_SERVER_COMMON_LIST
)

SET (HEADERFILES_SERVER_BILLING_MAIN_LIST
	../../../../include/server/billing/main/accounttable.h
	../../../../include/server/billing/main/billing.h
	../../../../include/server/billing/main/servermanager.h
)

SET (HEADERFILES_SERVER_BILLING_CONNECTION_LIST
	../../../../include/server/billing/connection/billing.h
	../../../../include/server/billing/connection/manager.h
	../../../../include/server/billing/connection/pool.h
	../../../../include/server/billing/connection/server.h
)

SET (HEADERFILES_SERVER_BILLING_LIST
)

SET (HEADERFILES_SERVER_LIST
)

SET (HEADERFILES_COMMON_BASE_LIST
	../../../../include/common/base/config.h
	../../../../include/common/base/io.h
	../../../../include/common/base/md5.h
	../../../../include/common/base/string.h
	../../../../include/common/base/type.h
	../../../../include/common/base/util.h
)

SET (HEADERFILES_COMMON_SYS_LIST
	../../../../include/common/sys/assert.h
	../../../../include/common/sys/config.h
	../../../../include/common/sys/minidump.h
	../../../../include/common/sys/thread.h
	../../../../include/common/sys/util.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_ATTRIBUTE_LIST
	../../../../include/common/game/define/attribute/all.h
	../../../../include/common/game/define/attribute/character.h
	../../../../include/common/game/define/attribute/monster.h
	../../../../include/common/game/define/attribute/pet.h
	../../../../include/common/game/define/attribute/teammember.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_ERROR_LIST
	../../../../include/common/game/define/error/all.h
	../../../../include/common/game/define/error/attack.h
	../../../../include/common/game/define/error/channel.h
	../../../../include/common/game/define/error/team.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_GROUP_LIST
	../../../../include/common/game/define/group/all.h
	../../../../include/common/game/define/group/relation.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_ID_LIST
	../../../../include/common/game/define/id/ability.h
	../../../../include/common/game/define/id/all.h
	../../../../include/common/game/define/id/impact.h
	../../../../include/common/game/define/id/packet.h
	../../../../include/common/game/define/id/skill.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_INDEX_LIST
	../../../../include/common/game/define/index/all.h
	../../../../include/common/game/define/index/skill.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_RESULT_LIST
	../../../../include/common/game/define/result/all.h
	../../../../include/common/game/define/result/channel.h
	../../../../include/common/game/define/result/login.h
	../../../../include/common/game/define/result/team.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_SIZE_LIST
	../../../../include/common/game/define/size/all.h
	../../../../include/common/game/define/size/mibao.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_STATUS_LIST
	../../../../include/common/game/define/status/all.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_TIME_LIST
	../../../../include/common/game/define/time/all.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_TYPE_LIST
	../../../../include/common/game/define/type/all.h
	../../../../include/common/game/define/type/attack.h
	../../../../include/common/game/define/type/chat.h
	../../../../include/common/game/define/type/command.h
	../../../../include/common/game/define/type/event.h
	../../../../include/common/game/define/type/human.h
	../../../../include/common/game/define/type/mail.h
	../../../../include/common/game/define/type/monster.h
	../../../../include/common/game/define/type/relation.h
	../../../../include/common/game/define/type/setting.h
	../../../../include/common/game/define/type/shop.h
	../../../../include/common/game/define/type/skill.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_VALUE_LIST
	../../../../include/common/game/define/value/all.h
	../../../../include/common/game/define/value/combat.h
	../../../../include/common/game/define/value/pk.h
	../../../../include/common/game/define/value/relation.h
)

SET (HEADERFILES_COMMON_GAME_DEFINE_LIST
	../../../../include/common/game/define/all.h
	../../../../include/common/game/define/enum.h
	../../../../include/common/game/define/macros.h
)

SET (HEADERFILES_COMMON_GAME_CLASSES_LIST
	../../../../include/common/game/classes/all.h
)

SET (HEADERFILES_COMMON_GAME_STRUCTS_LIST
	../../../../include/common/game/structs/all.h
	../../../../include/common/game/structs/impact.h
	../../../../include/common/game/structs/skill.h
)

SET (HEADERFILES_COMMON_GAME_LIST
	../../../../include/common/game/config.h
	../../../../include/common/game/util.h
)

SET (HEADERFILES_COMMON_FILE_LIST
	../../../../include/common/file/config.h
	../../../../include/common/file/database.h
	../../../../include/common/file/ini.h
)

SET (HEADERFILES_COMMON_LIB_ICONV_LIST
	../../../../include/common/lib/iconv/iconv.h
)

SET (HEADERFILES_COMMON_LIB_VNET_LIST
	../../../../include/common/lib/vnet/vnet.h
	../../../../include/common/lib/vnet/vnet.hpp
	../../../../include/common/lib/vnet/vnetapi.h
	../../../../include/common/lib/vnet/vnetconf.h
	../../../../include/common/lib/vnet/vnetlib.h
)

SET (HEADERFILES_COMMON_LIB_LIST
)

SET (HEADERFILES_COMMON_NET_SOCKET_LIST
	../../../../include/common/net/socket/base.h
	../../../../include/common/net/socket/inputstream.h
	../../../../include/common/net/socket/outputstream.h
)

SET (HEADERFILES_COMMON_NET_PACKET_LIST
	../../../../include/common/net/packet/base.h
	../../../../include/common/net/packet/factory.h
	../../../../include/common/net/packet/factorymanager.h
)

SET (HEADERFILES_COMMON_NET_LIST
	../../../../include/common/net/config.h
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
	source_group(SourceFiles\\common\\net\\packet FILES ${SOURCEFILES_COMMON_NET_PACKET_LIST})
	source_group(SourceFiles\\common\\net\\socket FILES ${SOURCEFILES_COMMON_NET_SOCKET_LIST})
	source_group(SourceFiles\\common\\net FILES ${SOURCEFILES_COMMON_NET_LIST})
	source_group(SourceFiles\\common FILES ${SOURCEFILES_COMMON_LIST})
	source_group(SourceFiles\\server\\common\\game FILES ${SOURCEFILES_SERVER_COMMON_GAME_LIST})
	source_group(SourceFiles\\server\\common\\net\\packets\\billing\\tologin FILES ${SOURCEFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST})
	source_group(SourceFiles\\server\\common\\net\\packets\\login\\tobilling FILES ${SOURCEFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST})
	source_group(SourceFiles\\server\\common\\net\\packets FILES ${SOURCEFILES_SERVER_COMMON_NET_PACKETS_LIST})
	source_group(SourceFiles\\server\\common\\net\\connection FILES ${SOURCEFILES_SERVER_COMMON_NET_CONNECTION_LIST})
	source_group(SourceFiles\\server\\common\\net FILES ${SOURCEFILES_SERVER_COMMON_NET_LIST})
	source_group(SourceFiles\\server\\common\\base FILES ${SOURCEFILES_SERVER_COMMON_BASE_LIST})
	source_group(SourceFiles\\server\\common\\sys FILES ${SOURCEFILES_SERVER_COMMON_SYS_LIST})
	source_group(SourceFiles\\server\\common FILES ${SOURCEFILES_SERVER_COMMON_LIST})
	source_group(SourceFiles\\server\\billing\\src\\main FILES ${SOURCEFILES_SERVER_BILLING_SRC_MAIN_LIST})
	source_group(SourceFiles\\server\\billing\\src\\connection FILES ${SOURCEFILES_SERVER_BILLING_SRC_CONNECTION_LIST})
	source_group(SourceFiles\\server\\billing\\src\\packets\\handler\\billing\\tologin FILES ${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_BILLING_TOLOGIN_LIST})
	source_group(SourceFiles\\server\\billing\\src\\packets\\handler\\login\\tobilling FILES ${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LOGIN_TOBILLING_LIST})
	source_group(SourceFiles\\server\\billing\\src\\packets\\handler FILES ${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LIST})
	source_group(SourceFiles\\server\\billing\\src\\packets FILES ${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_LIST})
	source_group(SourceFiles\\server\\billing\\src FILES ${SOURCEFILES_SERVER_BILLING_SRC_LIST})
	source_group(SourceFiles\\server\\billing FILES ${SOURCEFILES_SERVER_BILLING_LIST})
	source_group(SourceFiles\\server FILES ${SOURCEFILES_SERVER_LIST})
	source_group(SourceFiles FILES ${SOURCEFILES_LIST})
	source_group(HeaderFiles\\server\\common\\base FILES ${HEADERFILES_SERVER_COMMON_BASE_LIST})
	source_group(HeaderFiles\\server\\common\\net\\connection FILES ${HEADERFILES_SERVER_COMMON_NET_CONNECTION_LIST})
	source_group(HeaderFiles\\server\\common\\net\\packets\\billing\\tologin FILES ${HEADERFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST})
	source_group(HeaderFiles\\server\\common\\net\\packets\\login\\tobilling FILES ${HEADERFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST})
	source_group(HeaderFiles\\server\\common\\net\\packets FILES ${HEADERFILES_SERVER_COMMON_NET_PACKETS_LIST})
	source_group(HeaderFiles\\server\\common\\net FILES ${HEADERFILES_SERVER_COMMON_NET_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define\\type FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_TYPE_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define\\id\\packet FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_PACKET_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define\\id FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define\\status FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_STATUS_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define\\result FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_RESULT_LIST})
	source_group(HeaderFiles\\server\\common\\game\\define FILES ${HEADERFILES_SERVER_COMMON_GAME_DEFINE_LIST})
	source_group(HeaderFiles\\server\\common\\game FILES ${HEADERFILES_SERVER_COMMON_GAME_LIST})
	source_group(HeaderFiles\\server\\common\\sys FILES ${HEADERFILES_SERVER_COMMON_SYS_LIST})
	source_group(HeaderFiles\\server\\common FILES ${HEADERFILES_SERVER_COMMON_LIST})
	source_group(HeaderFiles\\server\\billing\\main FILES ${HEADERFILES_SERVER_BILLING_MAIN_LIST})
	source_group(HeaderFiles\\server\\billing\\connection FILES ${HEADERFILES_SERVER_BILLING_CONNECTION_LIST})
	source_group(HeaderFiles\\server\\billing FILES ${HEADERFILES_SERVER_BILLING_LIST})
	source_group(HeaderFiles\\server FILES ${HEADERFILES_SERVER_LIST})
	source_group(HeaderFiles\\common\\base FILES ${HEADERFILES_COMMON_BASE_LIST})
	source_group(HeaderFiles\\common\\sys FILES ${HEADERFILES_COMMON_SYS_LIST})
	source_group(HeaderFiles\\common\\game\\define\\attribute FILES ${HEADERFILES_COMMON_GAME_DEFINE_ATTRIBUTE_LIST})
	source_group(HeaderFiles\\common\\game\\define\\error FILES ${HEADERFILES_COMMON_GAME_DEFINE_ERROR_LIST})
	source_group(HeaderFiles\\common\\game\\define\\group FILES ${HEADERFILES_COMMON_GAME_DEFINE_GROUP_LIST})
	source_group(HeaderFiles\\common\\game\\define\\id FILES ${HEADERFILES_COMMON_GAME_DEFINE_ID_LIST})
	source_group(HeaderFiles\\common\\game\\define\\index FILES ${HEADERFILES_COMMON_GAME_DEFINE_INDEX_LIST})
	source_group(HeaderFiles\\common\\game\\define\\result FILES ${HEADERFILES_COMMON_GAME_DEFINE_RESULT_LIST})
	source_group(HeaderFiles\\common\\game\\define\\size FILES ${HEADERFILES_COMMON_GAME_DEFINE_SIZE_LIST})
	source_group(HeaderFiles\\common\\game\\define\\status FILES ${HEADERFILES_COMMON_GAME_DEFINE_STATUS_LIST})
	source_group(HeaderFiles\\common\\game\\define\\time FILES ${HEADERFILES_COMMON_GAME_DEFINE_TIME_LIST})
	source_group(HeaderFiles\\common\\game\\define\\type FILES ${HEADERFILES_COMMON_GAME_DEFINE_TYPE_LIST})
	source_group(HeaderFiles\\common\\game\\define\\value FILES ${HEADERFILES_COMMON_GAME_DEFINE_VALUE_LIST})
	source_group(HeaderFiles\\common\\game\\define FILES ${HEADERFILES_COMMON_GAME_DEFINE_LIST})
	source_group(HeaderFiles\\common\\game\\classes FILES ${HEADERFILES_COMMON_GAME_CLASSES_LIST})
	source_group(HeaderFiles\\common\\game\\structs FILES ${HEADERFILES_COMMON_GAME_STRUCTS_LIST})
	source_group(HeaderFiles\\common\\game FILES ${HEADERFILES_COMMON_GAME_LIST})
	source_group(HeaderFiles\\common\\file FILES ${HEADERFILES_COMMON_FILE_LIST})
	source_group(HeaderFiles\\common\\lib\\iconv FILES ${HEADERFILES_COMMON_LIB_ICONV_LIST})
	source_group(HeaderFiles\\common\\lib\\vnet FILES ${HEADERFILES_COMMON_LIB_VNET_LIST})
	source_group(HeaderFiles\\common\\lib FILES ${HEADERFILES_COMMON_LIB_LIST})
	source_group(HeaderFiles\\common\\net\\socket FILES ${HEADERFILES_COMMON_NET_SOCKET_LIST})
	source_group(HeaderFiles\\common\\net\\packet FILES ${HEADERFILES_COMMON_NET_PACKET_LIST})
	source_group(HeaderFiles\\common\\net FILES ${HEADERFILES_COMMON_NET_LIST})
	source_group(HeaderFiles\\common FILES ${HEADERFILES_COMMON_LIST})
	source_group(HeaderFiles FILES ${HEADERFILES_LIST})
	source_group(ResourceFiles FILES ${RESOURCEFILES_LIST})
endif()


ADD_EXECUTABLE(billing
	${SOURCEFILES_COMMON_BASE_LIST}
	${SOURCEFILES_COMMON_SYS_LIST}
	${SOURCEFILES_COMMON_FILE_LIST}
	${SOURCEFILES_COMMON_NET_PACKET_LIST}
	${SOURCEFILES_COMMON_NET_SOCKET_LIST}
	${SOURCEFILES_COMMON_NET_LIST}
	${SOURCEFILES_COMMON_LIST}
	${SOURCEFILES_SERVER_COMMON_GAME_LIST}
	${SOURCEFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST}
	${SOURCEFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST}
	${SOURCEFILES_SERVER_COMMON_NET_PACKETS_LIST}
	${SOURCEFILES_SERVER_COMMON_NET_CONNECTION_LIST}
	${SOURCEFILES_SERVER_COMMON_NET_LIST}
	${SOURCEFILES_SERVER_COMMON_BASE_LIST}
	${SOURCEFILES_SERVER_COMMON_SYS_LIST}
	${SOURCEFILES_SERVER_COMMON_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_MAIN_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_CONNECTION_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_BILLING_TOLOGIN_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LOGIN_TOBILLING_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_HANDLER_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_PACKETS_LIST}
	${SOURCEFILES_SERVER_BILLING_SRC_LIST}
	${SOURCEFILES_SERVER_BILLING_LIST}
	${SOURCEFILES_SERVER_LIST}
	${SOURCEFILES_LIST}
	${HEADERFILES_SERVER_COMMON_BASE_LIST}
	${HEADERFILES_SERVER_COMMON_NET_CONNECTION_LIST}
	${HEADERFILES_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_LIST}
	${HEADERFILES_SERVER_COMMON_NET_PACKETS_LOGIN_TOBILLING_LIST}
	${HEADERFILES_SERVER_COMMON_NET_PACKETS_LIST}
	${HEADERFILES_SERVER_COMMON_NET_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_TYPE_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_PACKET_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_ID_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_STATUS_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_RESULT_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_DEFINE_LIST}
	${HEADERFILES_SERVER_COMMON_GAME_LIST}
	${HEADERFILES_SERVER_COMMON_SYS_LIST}
	${HEADERFILES_SERVER_COMMON_LIST}
	${HEADERFILES_SERVER_BILLING_MAIN_LIST}
	${HEADERFILES_SERVER_BILLING_CONNECTION_LIST}
	${HEADERFILES_SERVER_BILLING_LIST}
	${HEADERFILES_SERVER_LIST}
	${HEADERFILES_COMMON_BASE_LIST}
	${HEADERFILES_COMMON_SYS_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_ATTRIBUTE_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_ERROR_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_GROUP_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_ID_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_INDEX_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_RESULT_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_SIZE_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_STATUS_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_TIME_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_TYPE_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_VALUE_LIST}
	${HEADERFILES_COMMON_GAME_DEFINE_LIST}
	${HEADERFILES_COMMON_GAME_CLASSES_LIST}
	${HEADERFILES_COMMON_GAME_STRUCTS_LIST}
	${HEADERFILES_COMMON_GAME_LIST}
	${HEADERFILES_COMMON_FILE_LIST}
	${HEADERFILES_COMMON_LIB_ICONV_LIST}
	${HEADERFILES_COMMON_LIB_VNET_LIST}
	${HEADERFILES_COMMON_LIB_LIST}
	${HEADERFILES_COMMON_NET_SOCKET_LIST}
	${HEADERFILES_COMMON_NET_PACKET_LIST}
	${HEADERFILES_COMMON_NET_LIST}
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
TARGET_LINK_LIBRARIES(billing ws2_32.lib odbc32.lib odbccp32.lib iconv.lib libvnet.lib)
else()
TARGET_LINK_LIBRARIES(billing pthread odbc iconv vnet)
  if(USE_32BITS)
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
  else()
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
  endif(USE_32BITS)
endif(WIN32)
