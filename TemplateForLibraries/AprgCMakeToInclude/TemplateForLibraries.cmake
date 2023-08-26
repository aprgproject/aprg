# Assign project directory, this needs aprg directory
set(TEMPLATE_FOR_LIBRARIES_DIR ${APRG_DIR}/TemplateForLibraries/TemplateForLibraries/)

# Assign files, directories, flags, definitions and other specific steps
include(${TEMPLATE_FOR_LIBRARIES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${TEMPLATE_FOR_LIBRARIES_INCLUDE_DIRECTORIES})
add_library(TEMPLATE_FOR_LIBRARIES ${TEMPLATE_FOR_LIBRARIES_SOURCES})
