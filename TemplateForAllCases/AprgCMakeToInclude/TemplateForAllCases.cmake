# Assign project directory, this needs aprg directory
set(TEMPLATE_FOR_ALL_CASES_DIR ${APRG_DIR}/TemplateForAllCases/TemplateForAllCases/)

# Assign files, directories, flags, definitions and other specific steps
include(${TEMPLATE_FOR_ALL_CASES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${TEMPLATE_FOR_ALL_CASES_INCLUDE_DIRECTORIES})
add_library(TEMPLATE_FOR_ALL_CASES ${TEMPLATE_FOR_ALL_CASES_SOURCES})
