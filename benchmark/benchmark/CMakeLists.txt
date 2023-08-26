cmake_minimum_required(VERSION 3.16)

# Set project details
project(benchmark C CXX)
set(OUTFILE ${PROJECT_NAME})
set(BENCHMARK_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BENCHMARK_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../benchmarkLibrary/)

# Locate APRG Directory first because its used on other cmakes
include(${BENCHMARK_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${BENCHMARK_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${BENCHMARK_SOURCES_AND_TESTS})
print_variable(BENCHMARK_INCLUDE_DIRECTORIES)
include_directories(${BENCHMARK_INCLUDE_DIRECTORIES} ${BENCHMARK_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_SHLWAPI_DEPENDENCIES} ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
