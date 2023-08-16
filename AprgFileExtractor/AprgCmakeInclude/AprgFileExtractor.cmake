# Assign project directory, this needs aprg directory
set(APRG_FILE_EXTRACTOR_DIR ${APRG_DIR}/AprgFileExtractor/AprgFileExtractor/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES})
add_library(APRG_FILE_EXTRACTOR ${APRG_FILE_EXTRACTOR_SOURCES})
