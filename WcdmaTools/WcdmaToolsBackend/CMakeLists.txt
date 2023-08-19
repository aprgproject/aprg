cmake_minimum_required(VERSION 3.16)

# Set project details
project(WcdmaToolsBackend C CXX)
set(OUTFILE ${PROJECT_NAME})
set(WCDMA_TOOLS_BACKEND_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${WCDMA_TOOLS_BACKEND_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${WCDMA_TOOLS_BACKEND_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${WCDMA_TOOLS_BACKEND_SOURCES_AND_TESTS})
include_directories(${WCDMA_TOOLS_BACKEND_INCLUDE_DIRECTORIES} ${WCDMA_TOOLS_BACKEND_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_COMMON APRG_GREP_STRING_EVALUATOR ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
