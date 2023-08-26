cmake_minimum_required(VERSION 3.16)

# Set project details
project(BtsTraceDecoder C CXX)
set(OUTFILE ${PROJECT_NAME})
set(BTS_TRACE_DECODER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${BTS_TRACE_DECODER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${BTS_TRACE_DECODER_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${BTS_TRACE_DECODER_SOURCES_AND_TESTS})
    include_directories(${BTS_TRACE_DECODER_INCLUDE_DIRECTORIES} ${BTS_TRACE_DECODER_TEST_INCLUDE_DIRECTORIES}
                        ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${BTS_TRACE_DECODER_SOURCES} ${BTS_TRACE_DECODER_MAIN_SOURCES})
    include_directories(${BTS_TRACE_DECODER_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
