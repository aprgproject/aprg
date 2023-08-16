# Assign project directory, this needs aprg directory
set(APRG_BOOLEAN_ALGEBRA_DIR ${APRG_DIR}/AprgBooleanAlgebra/AprgBooleanAlgebra/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_BOOLEAN_ALGEBRA_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_BOOLEAN_ALGEBRA_INCLUDE_DIRECTORIES})
add_library(APRG_BOOLEAN_ALGEBRA ${APRG_BOOLEAN_ALGEBRA_SOURCES})
