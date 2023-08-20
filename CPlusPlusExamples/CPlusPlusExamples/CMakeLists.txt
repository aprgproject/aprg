cmake_minimum_required(VERSION 3.16)

# Set project details
project(CPlusPlusExamples C CXX)
set(OUTFILE ${PROJECT_NAME})
set(C_PLUS_PLUS_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${C_PLUS_PLUS_EXAMPLES_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${C_PLUS_PLUS_EXAMPLES_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${C_PLUS_PLUS_EXAMPLES_SOURCES_AND_TESTS})
include_directories(${C_PLUS_PLUS_EXAMPLES_INCLUDE_DIRECTORIES} ${C_PLUS_PLUS_EXAMPLES_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
