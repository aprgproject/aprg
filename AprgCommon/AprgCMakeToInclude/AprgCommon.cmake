# Assign project directory, this needs aprg directory
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_COMMON_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES})
add_library(APRG_COMMON ${APRG_COMMON_SOURCES})
