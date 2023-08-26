cmake_minimum_required(VERSION 3.16)

# Set project details
project(SOOSA C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SOOSA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${SOOSA_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${SOOSA_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${SOOSA_SOURCES_AND_TESTS})
    include_directories(${SOOSA_INCLUDE_DIRECTORIES} ${SOOSA_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_BITMAP APRG_GEOMETRY APRG_STATISTICS APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${SOOSA_SOURCES} ${SOOSA_MAIN_SOURCES})
    include_directories(${SOOSA_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_BITMAP APRG_GEOMETRY APRG_STATISTICS APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
