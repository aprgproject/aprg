cmake_minimum_required(VERSION 3.16)

# Set project details
project(GoogleKickStart C CXX)
set(OUTFILE ${PROJECT_NAME})
set(GOOGLE_KICK_START_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${GOOGLE_KICK_START_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${GOOGLE_KICK_START_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${GOOGLE_KICK_START_SOURCES_AND_TESTS})
include_directories(${GOOGLE_KICK_START_INCLUDE_DIRECTORIES} ${GOOGLE_KICK_START_TEST_INCLUDE_DIRECTORIES}
                    ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
