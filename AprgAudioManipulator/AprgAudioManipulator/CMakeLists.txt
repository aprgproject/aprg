cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgAudioManipulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_AUDIO_MANIPULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set APRG_TEST_MODE to ON to enable tests and OFF to call main function.
option(APRG_TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAudio/AprgCmakeInclude/AprgAudio.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if (APRG_TEST_MODE)
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES_AND_TESTS})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES} ${APRG_AUDIO_MANIPULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_AUDIO APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES} ${APRG_AUDIO_MANIPULATOR_MAIN_SOURCES})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_AUDIO APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
