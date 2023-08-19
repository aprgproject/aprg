cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgFileExtractor C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_FILE_EXTRACTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if (APRG_TEST_MODE)
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES_AND_TESTS})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES} ${APRG_FILE_EXTRACTOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_GREP_STRING_EVALUATOR ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES} ${APRG_FILE_EXTRACTOR_MAIN_SOURCES})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_GREP_STRING_EVALUATOR)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)


