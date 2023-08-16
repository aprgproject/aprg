cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgGrepStringEvaluator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_GREP_STRING_EVALUATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_GREP_STRING_EVALUATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GREP_STRING_EVALUATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_GREP_STRING_EVALUATOR_SOURCES_AND_TESTS})
include_directories(${APRG_GREP_STRING_EVALUATOR_INCLUDE_DIRECTORIES} ${APRG_GREP_STRING_EVALUATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
