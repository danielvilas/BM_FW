find_library(LIB_YAML yaml)
IF(LIB_YAML)
    MESSAGE(STATUS "YAML libraries founded: OK ${LIB_YAML}")
ENDIF(LIB_YAML)

IF(NOT LIB_YAML)
    MESSAGE(FATAL_ERROR "ERROR: unable to link YAML")
ENDIF(NOT LIB_YAML)