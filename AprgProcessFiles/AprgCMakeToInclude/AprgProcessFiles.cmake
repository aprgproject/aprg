# Assign project directory, this needs aprg directory
set(APRG_PROCESS_FILES_DIR ${APRG_DIR}/AprgProcessFiles/AprgProcessFiles/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_PROCESS_FILES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_PROCESS_FILES_INCLUDE_DIRECTORIES})
add_library(APRG_PROCESS_FILES ${APRG_PROCESS_FILES_SOURCES})
