cmake_minimum_required(VERSION 3.9)
project(BmCoordinator LANGUAGES C VERSION 0.1.0)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_STANDARD 99)

include(libYaml)

set(DATALOGGER_SOURCE_FILES rp_datalogger/dataloger.c)
set(CONFIG_SOURCE_FILES bmCoordinator/config.c bmCoordinator/config.h)
set(COMMON_SOURCE_FILES bmCoordinator/proc_common.c bmCoordinator/proc_common.h)
set(REMOTE_SOURCE_FILES bmCoordinator/remote_proc.c bmCoordinator/remote_proc.h)
set(LOCAL_SOURCE_FILES bmCoordinator/datalogger.c bmCoordinator/datalogger.h)


add_executable(bmCoordinator ${CONFIG_SOURCE_FILES} ${COMMON_SOURCE_FILES} ${REMOTE_SOURCE_FILES} ${LOCAL_SOURCE_FILES} bmCoordinator/main.c)
target_link_libraries(bmCoordinator  yaml ${LIBS_SYSTEM})

add_executable(rp_datalogger ${DATALOGGER_SOURCE_FILES})
target_link_libraries(rp_datalogger  ${LIBS_SYSTEM})

