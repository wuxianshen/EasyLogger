
set(OS_EASYLOG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/easylogger-fork/demo/os/linux/easylogger)

##################
## Include_Dirs ##
##################
#Place OS related header files in front
#OS related header files take effect if there are homonymic header files
include_directories(${OS_EASYLOG_PATH}/inc)
include_directories(${OS_EASYLOG_PATH}/plugins)

include_directories(easylogger-fork/easylogger/inc)
include_directories(easylogger-fork/easylogger/plugins)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)

##################
## Source_Dirs  ##
##################
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/easylogger-fork/easylogger/src/ ELOG_SOURCES)
aux_source_directory(${OS_EASYLOG_PATH}/plugins/file/   ELOG_SOURCES)
aux_source_directory(${OS_EASYLOG_PATH}/plugins/socket/ ELOG_SOURCES)
aux_source_directory(${OS_EASYLOG_PATH}/port/           ELOG_SOURCES)

set(ELOG_FILE_IMP   "${CMAKE_CURRENT_SOURCE_DIR}/easylogger-fork/easylogger/plugins/file/elog_file.c")
set(ELOG_SOCKET_IMP "${CMAKE_CURRENT_SOURCE_DIR}/easylogger-fork/easylogger/plugins/socket/elog_socket.c")
set(ELOG_SOURCES "${ELOG_SOURCES};${ELOG_FILE_IMP};${ELOG_SOCKET_IMP}")
