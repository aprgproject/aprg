# Assign project directory, this needs aprg directory
set(WCDMA_TOOLS_BACKEND_DIR ${APRG_DIR}/WcdmaTools/WcdmaToolsBackend/)

# Assign files, directories, flags, definitions and other specific steps
include(${WCDMA_TOOLS_BACKEND_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${WCDMA_TOOLS_BACKEND_INCLUDE_DIRECTORIES})
add_library(WCDMA_TOOLS_BACKEND ${WCDMA_TOOLS_BACKEND_SOURCES})
