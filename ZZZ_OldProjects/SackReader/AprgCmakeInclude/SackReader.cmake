#Assign AprgCommon directory, this needs aprg directory
set(SACK_READER_DIR ${APRG_DIR}/SackReader/SackReader/)

#Include APRG_COMMON files and directories
include(${SACK_READER_DIR}/cmake/FindFilesAndDirectories.cmake))

include_directories(${SACK_READER_INCLUDE_DIRECTORIES})
add_library(SACK_READER ${SACK_READER_SOURCES})
