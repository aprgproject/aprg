# Assign project directory, this needs aprg directory
set(APRG_CPP_CODE_UTILITIES_DIR ${APRG_DIR}/AprgCppCodeUtilities/AprgCppCodeUtilities/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_CPP_CODE_UTILITIES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_CPP_CODE_UTILITIES_INCLUDE_DIRECTORIES})
add_library(APRG_CPP_CODE_UTILITIES ${APRG_CPP_CODE_UTILITIES_SOURCES})
