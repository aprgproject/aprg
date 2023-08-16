cmake_minimum_required(VERSION 3.16)

# Set project details
project(SnapshotStatistics C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SNAPSHOT_DETAILS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set TEST_MODE to ON to enable tests and OFF to call main function.
option(TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${SNAPSHOT_DETAILS_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Assign specific definitions
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)

# Process for files, directories and flags
include(${SNAPSHOT_DETAILS_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${SNAPSHOT_DETAILS_DIR}/cmake/AddFlags.cmake)

# Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${SNAPSHOT_DETAILS_SOURCES_AND_TESTS})
    include_directories(${SNAPSHOT_DETAILS_INCLUDE_DIRECTORIES} ${SNAPSHOT_DETAILS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${SNAPSHOT_DETAILS_SOURCES} ${SNAPSHOT_DETAILS_MAIN_SOURCES})
    include_directories(${SNAPSHOT_DETAILS_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_FILE_EXTRACTOR APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
