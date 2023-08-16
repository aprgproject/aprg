# Assign project directory, this needs aprg directory
set(RTT_ANALYZER_DIR ${APRG_DIR}/RttAnalyzer/RttAnalyzer/)

# Assign files, directories, flags, definitions and other specific steps
include(${RTT_ANALYZER_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${RTT_ANALYZER_INCLUDE_DIRECTORIES})
add_library(RTT_ANALYZER ${RTT_ANALYZER_SOURCES})
