# Assign project directory, this needs aprg directory
set(APRG_STATISTICS_DIR ${APRG_DIR}/AprgStatistics/AprgStatistics/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_STATISTICS_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_STATISTICS_INCLUDE_DIRECTORIES})
add_library(APRG_STATISTICS ${APRG_STATISTICS_SOURCES})
