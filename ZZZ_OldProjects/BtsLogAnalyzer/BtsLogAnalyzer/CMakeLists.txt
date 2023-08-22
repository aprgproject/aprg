cmake_minimum_required(VERSION 3.16)

# Set project details
project(BtsLogAnalyzer C CXX)
set(OUTFILE ${PROJECT_NAME})
set(BTS_LOG_ANALYZER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${BTS_LOG_ANALYZER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/WcdmaTools/AprgCmakeInclude/WcdmaToolsBackend.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${BTS_LOG_ANALYZER_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${BTS_LOG_ANALYZER_SOURCES_AND_TESTS})
include_directories(${BTS_LOG_ANALYZER_INCLUDE_DIRECTORIES} ${BTS_LOG_ANALYZER_TEST_INCLUDE_DIRECTORIES}
                    ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_GREP_STRING_EVALUATOR WCDMA_TOOLS_BACKEND APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
