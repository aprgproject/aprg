cmake_minimum_required(VERSION 3.16)

# Set project details
project(ChessUtilities C CXX)
set(OUTFILE ${PROJECT_NAME})
set(CHESS_UTILITIES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${CHESS_UTILITIES_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Process for files, directories and flags
include(${CHESS_UTILITIES_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${CHESS_UTILITIES_DIR}/cmake/AddFlags.cmake)

# Do final steps
add_executable(${OUTFILE} ${CHESS_UTILITIES_SOURCES_AND_TESTS})
include_directories(${CHESS_UTILITIES_INCLUDE_DIRECTORIES} ${CHESS_UTILITIES_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
