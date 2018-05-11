find_library(LIB_XLSX xlsxwriter)
IF(LIB_XLSX)
    MESSAGE(STATUS "XlsxWriter libraries founded: OK ${LIB_XLSX}")
ENDIF(LIB_XLSX)

IF(NOT LIB_XLSX)
    MESSAGE(FATAL_ERROR "ERROR: unable to link XlsxWriter")
ENDIF(NOT LIB_XLSX)