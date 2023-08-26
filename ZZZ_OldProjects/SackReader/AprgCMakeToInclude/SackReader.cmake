# Assign project directory, this needs aprg directory
set(SACK_READER_DIR ${APRG_DIR}/SackReader/SackReader/)

# Assign files, directories, flags, definitions and other specific steps
include(${SACK_READER_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${SACK_READER_INCLUDE_DIRECTORIES})
add_library(SACK_READER ${SACK_READER_SOURCES})
