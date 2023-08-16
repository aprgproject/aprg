# Assign project directory, this needs aprg directory
set(APRG_BITMAP_DIR ${APRG_DIR}/AprgBitmap/AprgBitmap/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_BITMAP_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_BITMAP_INCLUDE_DIRECTORIES})
add_library(APRG_BITMAP ${APRG_BITMAP_SOURCES})
