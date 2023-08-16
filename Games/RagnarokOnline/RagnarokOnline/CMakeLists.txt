cmake_minimum_required(VERSION 3.16)

# Set project details
project(RagnarokOnline C CXX)
set(OUTFILE ${PROJECT_NAME})
set(RAGNAROK_ONLINE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set APRG_TEST_MODE to ON to enable tests and OFF to call main function.
option(APRG_TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${RAGNAROK_ONLINE_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Process for files, directories and flags
include(${RAGNAROK_ONLINE_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${RAGNAROK_ONLINE_DIR}/cmake/AddFlags.cmake)

# Do final steps
if (APRG_TEST_MODE)
    add_executable(${OUTFILE} ${RAGNAROK_ONLINE_SOURCES_AND_TESTS})
    include_directories(${RAGNAROK_ONLINE_INCLUDE_DIRECTORIES} ${RAGNAROK_ONLINE_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${RAGNAROK_ONLINE_SOURCES} ${RAGNAROK_ONLINE_MAIN_SOURCES})
    include_directories(${RAGNAROK_ONLINE_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
