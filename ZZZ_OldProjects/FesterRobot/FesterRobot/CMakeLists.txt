cmake_minimum_required(VERSION 3.16)

# Set project details
project(FesterRobot C CXX)
set(OUTFILE ${PROJECT_NAME})
set(FESTER_ROBOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set TEST_MODE to ON to enable tests and OFF to call main function.
option(TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${FESTER_ROBOT_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCmakeInclude/AprgLocalUserAutomation.cmake)

# Process for files, directories and flags
include(${FESTER_ROBOT_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${FESTER_ROBOT_DIR}/cmake/AddFlags.cmake)

# Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES_AND_TESTS})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES} ${FESTER_ROBOT_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_LOCAL_USER_AUTOMATION APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES} ${FESTER_ROBOT_MAIN_SOURCES})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_LOCAL_USER_AUTOMATION APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
