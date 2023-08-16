# Assign project directory, this needs aprg directory
set(APRG_BITMAP_MANIPULATOR_DIR ${APRG_DIR}/AprgBitmapManipulator/AprgBitmapManipulator/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_BITMAP_MANIPULATOR_INCLUDE_DIRECTORIES})
add_library(APRG_BITMAP_MANIPULATOR ${APRG_BITMAP_MANIPULATOR_SOURCES})
