# Assign project directory, this needs aprg directory
set(APRG_GSL_DIR ${APRG_DIR}/AprgGsl/AprgGsl/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GSL_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_GSL_INCLUDE_DIRECTORIES})
add_library(APRG_GSL ${APRG_GSL_SOURCES})
