# Assign project directory, this needs aprg directory
set(APRG_ALGORITHM_DIR ${APRG_DIR}/AprgAlgorithm/AprgAlgorithm/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_ALGORITHM_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_ALGORITHM_INCLUDE_DIRECTORIES})
#add_library(APRG_ALGORITHM ${APRG_ALGORITHM_SOURCES}) # No CPP files
