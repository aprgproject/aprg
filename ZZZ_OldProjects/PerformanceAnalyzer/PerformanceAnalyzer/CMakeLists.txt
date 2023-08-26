cmake_minimum_required(VERSION 3.16)

# Set project details
project(PerformanceAnalyzer C CXX)
set(OUTFILE ${PROJECT_NAME})
set(PERFORMANCE_ANALYZER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${PERFORMANCE_ANALYZER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCMakeToInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgStatistics/AprgCMakeToInclude/AprgStatistics.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCMakeToInclude/AprgFileExtractor.cmake)
include(${APRG_DIR}/WcdmaTools/AprgCMakeToInclude/WcdmaToolsBackend.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCMakeToInclude/AprgGrepStringEvaluator.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${PERFORMANCE_ANALYZER_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${PERFORMANCE_ANALYZER_SOURCES_AND_TESTS})
include_directories(${PERFORMANCE_ANALYZER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(APRG_FILE_EXTRACTOR APRG_COMMON)
target_link_libraries(${OUTFILE} WCDMA_TOOLS_BACKEND APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_COMMON
                      ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
