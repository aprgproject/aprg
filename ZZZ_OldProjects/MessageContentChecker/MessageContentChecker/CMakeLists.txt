cmake_minimum_required(VERSION 3.16)

# Set project details
project(MessageContentChecker C CXX)
set(OUTFILE ${PROJECT_NAME})
set(MESSAGE_CONTENT_CHECKER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/SpecificStepsAsExecutable.cmake)

if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES_AND_TESTS} ${EXTERNAL_SACKS})
    include_directories(
        ${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${MESSAGE_CONTENT_CHECKER_TEST_INCLUDE_DIRECTORIES}
        ${EXTERNAL_SACK_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES} ${MESSAGE_CONTENT_CHECKER_MAIN_SOURCES})
    include_directories(${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
