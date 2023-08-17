# Assign files, directories, flags, definitions and other specific steps

include(${DD_CREATOR_DIR}/cmake/CommonFilesAndDirectories.cmake)
include(${DD_CREATOR_DIR}/cmake/ExternalSacks.cmake)
set(FEATURE_FOLDER "CNI21985")
include(${DD_CREATOR_DIR}/cmake/FeatureFilesAndDirectories.cmake)
set(DD_CREATOR_INCLUDE_DIRECTORIES ${DD_CREATOR_DIR}/src ${DD_CREATOR_DIR}/tst)

include(${DD_CREATOR_DIR}/cmake/AddFlags.cmake)
include(${DD_CREATOR_DIR}/cmake/AddDefinitions.cmake)
