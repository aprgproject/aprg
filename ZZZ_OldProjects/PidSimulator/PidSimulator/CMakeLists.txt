cmake_minimum_required(VERSION 3.16)

# Set project details
project(PidSimulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(PID_SIMULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${PID_SIMULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCMakeToInclude/AprgBitmap.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCMakeToInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgAlgebra/AprgCMakeToInclude/AprgAlgebra.cmake)
include(${APRG_DIR}/AprgGraph/AprgCMakeToInclude/AprgGraph.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${PID_SIMULATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if(APRG_TEST_MODE)
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES_AND_TESTS})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES} ${PID_SIMULATOR_TEST_INCLUDE_DIRECTORIES}
                        ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(
        ${OUTFILE}
        APRG_GRAPH
        APRG_ALGEBRA
        APRG_GEOMETRY
        APRG_BITMAP
        APRG_COMMON
        ${APRG_GTEST_DEPENDENCIES}) # add real time library
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES} ${PID_SIMULATOR_MAIN_SOURCES})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_GRAPH APRG_ALGEBRA APRG_GEOMETRY APRG_BITMAP APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
