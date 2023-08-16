cmake_minimum_required(VERSION 3.16)

# Set project details
project(QuickestWayToProgram C CXX)
set(OUTFILE ${PROJECT_NAME})
set(QUICKEST_WAY_TO_PROGRAM_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${QUICKEST_WAY_TO_PROGRAM_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Add specific definitions
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

# Process for files, directories and flags
include(${QUICKEST_WAY_TO_PROGRAM_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${QUICKEST_WAY_TO_PROGRAM_DIR}/cmake/AddFlags.cmake)

# Do final steps
add_executable(${OUTFILE} ${QUICKEST_WAY_TO_PROGRAM_SOURCES_AND_TESTS})
include_directories(${QUICKEST_WAY_TO_PROGRAM_INCLUDE_DIRECTORIES} ${QUICKEST_WAY_TO_PROGRAM_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
