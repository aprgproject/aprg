# Assign project directory, this needs aprg directory
set(APRG_CODE_UTILITIES_DIR ${APRG_DIR}/AprgCodeUtilities/AprgCodeUtilities/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_CODE_UTILITIES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_CODE_UTILITIES_INCLUDE_DIRECTORIES})
add_library(APRG_CODE_UTILITIES ${APRG_CODE_UTILITIES_SOURCES})
