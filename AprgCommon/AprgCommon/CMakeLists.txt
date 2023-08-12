cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgCommon C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${APRG_COMMON_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Process for files, directories and flags
include(${APRG_COMMON_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${APRG_COMMON_DIR}/cmake/AddFlags.cmake)

#Do final steps
add_executable(${OUTFILE} ${APRG_COMMON_SOURCES_AND_TESTS})
include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES} ${APRG_COMMON_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)

