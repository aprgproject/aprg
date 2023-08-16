# Assign project directory, this needs aprg directory
set(PID_SIMULATOR_DIR ${APRG_DIR}/PidSimulator/PidSimulator/)

# Assign files, directories, flags, definitions and other specific steps
include(${PID_SIMULATOR_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES})
add_library(PID_SIMULATOR ${PID_SIMULATOR_SOURCES})
