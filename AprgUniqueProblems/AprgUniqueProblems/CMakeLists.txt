cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgUniqueProblems C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_UNIQUE_PROBLEMS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set TEST_MODE to ON to enable tests and OFF to call main function.
option(TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${APRG_UNIQUE_PROBLEMS_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgMath/AprgCmakeInclude/AprgMath.cmake)

#Add Algorithm test files
include_directories(${APRG_ALGORITHM_TEST_INCLUDE_DIRECTORIES})

# Process for files, directories and flags
include(${APRG_UNIQUE_PROBLEMS_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${APRG_UNIQUE_PROBLEMS_DIR}/cmake/AddFlags.cmake)

# Do final steps
if(TEST_MODE)
    add_executable(${OUTFILE} ${APRG_UNIQUE_PROBLEMS_SOURCES_AND_TESTS})
    include_directories(${APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES} ${APRG_UNIQUE_PROBLEMS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_MATH APRG_GEOMETRY APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${APRG_UNIQUE_PROBLEMS_SOURCES} ${APRG_UNIQUE_PROBLEMS_MAIN_SOURCES})
    include_directories(${APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_MATH APRG_GEOMETRY APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
