cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgGsl C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_GSL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_GSL_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/gsl/AprgCmakeInclude/Gsl.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GSL_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_GSL_SOURCES_AND_TESTS})
include_directories(${APRG_GSL_INCLUDE_DIRECTORIES} ${APRG_GSL_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${GSL_LIBRARIES_TO_LINK} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
