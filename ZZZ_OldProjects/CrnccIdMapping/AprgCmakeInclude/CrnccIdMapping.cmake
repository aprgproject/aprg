# Assign project directory, this needs aprg directory
set(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR
    ${APRG_DIR}/SimplestDesignToCopyForLibraries/SimplestDesignToCopyForLibraries/)

# Assign files, directories, flags, definitions and other specific steps
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_INCLUDE_DIRECTORIES})
add_library(SIMPLEST_DESIGN_TO_COPY ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_SOURCES})
