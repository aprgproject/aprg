# Assign project directory, this needs aprg directory
set(APRG_GREP_STRING_EVALUATOR_DIR ${APRG_DIR}/AprgGrepStringEvaluator/AprgGrepStringEvaluator/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GREP_STRING_EVALUATOR_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_GREP_STRING_EVALUATOR_INCLUDE_DIRECTORIES})
add_library(APRG_GREP_STRING_EVALUATOR ${APRG_GREP_STRING_EVALUATOR_SOURCES})
