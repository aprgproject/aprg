cmake_minimum_required(VERSION 3.16)

# Set project details
project(ChessCombi C CXX)
set(OUTFILE ${PROJECT_NAME})
set(CHESS_COMBI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${CHESS_COMBI_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${CHESS_COMBI_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${CHESS_COMBI_SOURCES_AND_TESTS})
    include_directories(${CHESS_COMBI_INCLUDE_DIRECTORIES} ${CHESS_COMBI_TEST_INCLUDE_DIRECTORIES}
                        ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${CHESS_COMBI_SOURCES} ${CHESS_COMBI_MAIN_SOURCES})
    include_directories(${CHESS_COMBI_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
