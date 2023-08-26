# Assign project directory, this needs aprg directory
set(APRG_MATH_DIR ${APRG_DIR}/AprgMath/AprgMath/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_MATH_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_MATH_INCLUDE_DIRECTORIES})
add_library(APRG_MATH ${APRG_MATH_SOURCES})
