cmake_minimum_required(VERSION 3.16)

# Set project details
project(LrmAllocationSimulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(LRM_ALLOCATION_SIMULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${LRM_ALLOCATION_SIMULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${LRM_ALLOCATION_SIMULATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if (APRG_TEST_MODE)
    add_executable(${OUTFILE} ${LRM_ALLOCATION_SIMULATOR_SOURCES_AND_TESTS})
    include_directories(${LRM_ALLOCATION_SIMULATOR_INCLUDE_DIRECTORIES} ${LRM_ALLOCATION_SIMULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${LRM_ALLOCATION_SIMULATOR_SOURCES} ${LRM_ALLOCATION_SIMULATOR_MAIN_SOURCES})
    include_directories(${LRM_ALLOCATION_SIMULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
