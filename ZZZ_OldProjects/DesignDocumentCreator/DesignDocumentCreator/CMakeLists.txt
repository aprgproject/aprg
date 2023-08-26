cmake_minimum_required(VERSION 3.16)

# Set project details
project(DesignDocumentCreator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(DD_CREATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${DD_CREATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Assign specific definitions
add_definitions(-DCCS_BIG_ENDIAN)

# Assign DesignDocumentCreatorDirectory
set(DesignDocumentCreatorDirectory ${CMAKE_CURRENT_SOURCE_DIR})

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${DD_CREATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${DD_CREATOR_COMMON_SOURCES_AND_TESTS} ${FEATURE_SOURCES_AND_TESTS} ${EXTERNAL_SACKS})
include_directories(${FEATURE_INCLUDE_DIRECTORIES} ${DD_CREATOR_INCLUDE_DIRECTORIES} ${EXTERNAL_SACK_DIRECTORIES}
                    ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
