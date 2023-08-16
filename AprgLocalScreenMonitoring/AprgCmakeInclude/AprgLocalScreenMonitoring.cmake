# Assign project directory, this needs aprg directory
set(APRG_LOCAL_SCREEN_MONITORING_DIR ${APRG_DIR}/AprgLocalScreenMonitoring/AprgLocalScreenMonitoring/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_LOCAL_SCREEN_MONITORING_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_LOCAL_SCREEN_MONITORING_INCLUDE_DIRECTORIES})
add_library(APRG_LOCAL_SCREEN_MONITORING ${APRG_LOCAL_SCREEN_MONITORING_SOURCES})
