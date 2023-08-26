cmake_minimum_required(VERSION 3.16)

# Set project details
project(FesterRobot C CXX)
set(OUTFILE ${PROJECT_NAME})
set(FESTER_ROBOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${FESTER_ROBOT_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCMakeToInclude/AprgLocalUserAutomation.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${FESTER_ROBOT_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES_AND_TESTS})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES} ${FESTER_ROBOT_TEST_INCLUDE_DIRECTORIES}
                        ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_LOCAL_USER_AUTOMATION APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES} ${FESTER_ROBOT_MAIN_SOURCES})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_LOCAL_USER_AUTOMATION APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
