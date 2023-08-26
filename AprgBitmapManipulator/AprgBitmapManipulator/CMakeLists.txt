cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgBitmapManipulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_BITMAP_MANIPULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCMakeToInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCMakeToInclude/AprgBitmap.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCMakeToInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgStatistics/AprgCMakeToInclude/AprgStatistics.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_BITMAP_MANIPULATOR_SOURCES_AND_TESTS})
include_directories(${APRG_BITMAP_MANIPULATOR_INCLUDE_DIRECTORIES} ${APRG_BITMAP_MANIPULATOR_TEST_INCLUDE_DIRECTORIES}
                    ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_STATISTICS APRG_GEOMETRY APRG_BITMAP APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
