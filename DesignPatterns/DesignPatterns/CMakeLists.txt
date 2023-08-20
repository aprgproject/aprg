cmake_minimum_required(VERSION 3.16)

# Set project details
project(DesignPatterns C CXX)
set(OUTFILE ${PROJECT_NAME})
set(DESIGN_PATTERNS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${DESIGN_PATTERNS_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${DESIGN_PATTERNS_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${DESIGN_PATTERNS_SOURCES_AND_TESTS})
include_directories(${DESIGN_PATTERNS_INCLUDE_DIRECTORIES} ${DESIGN_PATTERNS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
add_test(${OUTFILE} ${OUTFILE})
