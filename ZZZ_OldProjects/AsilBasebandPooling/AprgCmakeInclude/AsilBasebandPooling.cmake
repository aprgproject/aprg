# Assign project directory, this needs aprg directory
set(ASIL_BASEBAND_POOLING_DIR ${APRG_DIR}/AsilBasebandPooling/AsilBasebandPooling/)

# Assign files, directories, flags, definitions and other specific steps
include(${ASIL_BASEBAND_POOLING_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${ASIL_BASEBAND_POOLING_INCLUDE_DIRECTORIES})
add_library(ASIL_BASEBAND_POOLING ${ASIL_BASEBAND_POOLING_SOURCES})
