cmake_minimum_required(VERSION 3.9)
project(DataExtractor LANGUAGES C VERSION 0.1.0)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_C_STANDARD 99)

set(CMAKE_C_STANDARD 99)

include(libYaml)
include(libXlsx)

set(CONFIG_SOURCE_FILES src/config.c src/config.h src/common.c src/common.h)
set(MEMORY_SOURCE_FILES src/memory.c src/memory.h )
set(POWER_SOURCE_FILES src/power.c src/power.h)

add_executable(DataExtractor ${CONFIG_SOURCE_FILES} ${MEMORY_SOURCE_FILES} ${POWER_SOURCE_FILES} src/main.c)
target_link_libraries(DataExtractor  xlsxwriter yaml ${LIBS_SYSTEM})