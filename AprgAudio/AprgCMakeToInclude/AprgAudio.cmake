# Assign project directory, this needs aprg directory
set(APRG_AUDIO_DIR ${APRG_DIR}/AprgAudio/AprgAudio/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_AUDIO_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_AUDIO_INCLUDE_DIRECTORIES})
add_library(APRG_AUDIO ${APRG_AUDIO_SOURCES})
