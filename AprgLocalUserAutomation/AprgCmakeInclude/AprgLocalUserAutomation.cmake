# Assign project directory, this needs aprg directory
set(APRG_LOCAL_USER_AUTOMATION_DIR ${APRG_DIR}/AprgLocalUserAutomation/AprgLocalUserAutomation/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_LOCAL_USER_AUTOMATION_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_LOCAL_USER_AUTOMATION_INCLUDE_DIRECTORIES})
add_library(APRG_LOCAL_USER_AUTOMATION ${APRG_LOCAL_USER_AUTOMATION_SOURCES})
