# Assign project directory, this needs aprg directory
set(APRG_AUDIO_MANIPULATOR_DIR ${APRG_DIR}/AprgAudioManipulator/AprgAudioManipulator/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES})
add_library(APRG_AUDIO_MANIPULATOR ${APRG_AUDIO_MANIPULATOR_SOURCES})
