# Assign project directory, this needs aprg directory
set(RAGNAROK_ONLINE_DIR ${APRG_DIR}/RagnarokOnline/RagnarokOnline/)

# Assign files, directories, flags, definitions and other specific steps
include(${RAGNAROK_ONLINE_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${RAGNAROK_ONLINE_INCLUDE_DIRECTORIES})
add_library(RAGNAROK_ONLINE ${RAGNAROK_ONLINE_SOURCES})
