cmake_minimum_required(VERSION 3.16)

# Set project details
project(SnapshotStatistics C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SNAPSHOT_DETAILS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${SNAPSHOT_DETAILS_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCMakeToInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCMakeToInclude/AprgGrepStringEvaluator.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCMakeToInclude/AprgFileExtractor.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${SNAPSHOT_DETAILS_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${SNAPSHOT_DETAILS_SOURCES_AND_TESTS})
    include_directories(${SNAPSHOT_DETAILS_INCLUDE_DIRECTORIES} ${SNAPSHOT_DETAILS_TEST_INCLUDE_DIRECTORIES}
                        ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_COMMON
                          ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${SNAPSHOT_DETAILS_SOURCES} ${SNAPSHOT_DETAILS_MAIN_SOURCES})
    include_directories(${SNAPSHOT_DETAILS_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_FILE_EXTRACTOR APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
