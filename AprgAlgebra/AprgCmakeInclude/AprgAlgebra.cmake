# Assign project directory, this needs aprg directory
set(APRG_ALGEBRA_DIR ${APRG_DIR}/AprgAlgebra/AprgAlgebra/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_ALGEBRA_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_ALGEBRA_INCLUDE_DIRECTORIES})
add_library(APRG_ALGEBRA ${APRG_ALGEBRA_SOURCES})
