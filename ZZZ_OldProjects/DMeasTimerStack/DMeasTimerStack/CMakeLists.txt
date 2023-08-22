cmake_minimum_required(VERSION 3.16)

# Set project details
project(DMeasTimerStack C CXX)
set(OUTFILE ${PROJECT_NAME})
set(DMEAS_TIMER_STACK_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${DMEAS_TIMER_STACK_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${DMEAS_TIMER_STACK_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${DMEAS_TIMER_STACK_SOURCES_AND_TESTS} ${EXTERNAL_SACKS})
    include_directories(${DMEAS_TIMER_STACK_INCLUDE_DIRECTORIES} ${DMEAS_TIMER_STACK_TEST_INCLUDE_DIRECTORIES}
                        ${EXTERNAL_SACK_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${DMEAS_TIMER_STACK_SOURCES} ${DMEAS_TIMER_STACK_MAIN_SOURCES} ${EXTERNAL_SACKS})
    include_directories(${DMEAS_TIMER_STACK_INCLUDE_DIRECTORIES} ${EXTERNAL_SACK_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
