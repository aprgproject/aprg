cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgProcessFiles C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_PROCESS_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_PROCESS_FILES_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

# Process for files, directories and flags
include(${APRG_PROCESS_FILES_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${APRG_PROCESS_FILES_DIR}/cmake/AddFlags.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_PROCESS_FILES_SOURCES_AND_TESTS})
include_directories(${APRG_PROCESS_FILES_INCLUDE_DIRECTORIES} ${APRG_PROCESS_FILES_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_GREP_STRING_EVALUATOR APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
