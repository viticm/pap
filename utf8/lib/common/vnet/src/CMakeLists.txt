SET(TF_CURRENT_BINARY_PATH_LIB "../static")
SET(LIBRARY_OUTPUT_PATH ${TF_CURRENT_BINARY_PATH_LIB})


##update_begin


INCLUDE_DIRECTORIES(../../../../include)


SET (SOURCEFILES_API_LIST
	../src/api/vnet.c
)

SET (SOURCEFILES_FILE_LIST
	../src/file/api.c
)

SET (SOURCEFILES_SOCKET_LIST
	../src/socket/api.c
	../src/socket/base.c
	../src/socket/endecode.c
	../src/socket/inputstream.c
	../src/socket/outputstream.c
)

SET (SOURCEFILES_BASE_LIST
	../src/base/io.c
)

SET (SOURCEFILES_LIST
)

SET (HEADERFILES_API_LIST
	../include/api/vnet.h
	../include/api/vnetapi.h
	../include/api/vnetconf.h
	../include/api/vnetlib.h
)

SET (HEADERFILES_BASE_LIST
	../include/base/io.h
	../include/base/type.h
)

SET (HEADERFILES_FILE_LIST
	../include/file/api.h
	../include/file/config.h
)

SET (HEADERFILES_SOCKET_LIST
	../include/socket/api.h
	../include/socket/base.h
	../include/socket/config.h
	../include/socket/endecode.h
	../include/socket/inputstream.h
	../include/socket/outputstream.h
)

SET (HEADERFILES_LIST
)



if (WIN32)
	source_group(SourceFiles\\api FILES ${SOURCEFILES_API_LIST})
	source_group(SourceFiles\\file FILES ${SOURCEFILES_FILE_LIST})
	source_group(SourceFiles\\socket FILES ${SOURCEFILES_SOCKET_LIST})
	source_group(SourceFiles\\base FILES ${SOURCEFILES_BASE_LIST})
	source_group(SourceFiles FILES ${SOURCEFILES_LIST})
	source_group(HeaderFiles\\api FILES ${HEADERFILES_API_LIST})
	source_group(HeaderFiles\\base FILES ${HEADERFILES_BASE_LIST})
	source_group(HeaderFiles\\file FILES ${HEADERFILES_FILE_LIST})
	source_group(HeaderFiles\\socket FILES ${HEADERFILES_SOCKET_LIST})
	source_group(HeaderFiles FILES ${HEADERFILES_LIST})
endif()


ADD_EXECUTABLE(vnet
	${SOURCEFILES_API_LIST}
	${SOURCEFILES_FILE_LIST}
	${SOURCEFILES_SOCKET_LIST}
	${SOURCEFILES_BASE_LIST}
	${SOURCEFILES_LIST}
	${HEADERFILES_API_LIST}
	${HEADERFILES_BASE_LIST}
	${HEADERFILES_FILE_LIST}
	${HEADERFILES_SOCKET_LIST}
	${HEADERFILES_LIST}
)


##update_end

IF(CMAKE_SYSTEM MATCHES Windows)
  TARGET_LINK_LIBRARIES(FoxNet ws2_32)
ELSE()
  if(USE_32BITS)
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
  else()
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
  endif(USE_32BITS)
ENDIF(CMAKE_SYSTEM MATCHES Windows)


