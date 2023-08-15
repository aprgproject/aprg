cmake_minimum_required(VERSION 3.16)

# Set project details
project(RevisionEditor C CXX)
set(OUTFILE ${PROJECT_NAME})
set(REVISION_EDITOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

# Locate APRG Directory first because its used on other cmakes
include(${REVISION_EDITOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Process for files, directories and flags
include(${REVISION_EDITOR_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${REVISION_EDITOR_DIR}/cmake/AddFlags.cmake)

# Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${REVISION_EDITOR_SOURCES_AND_TESTS})
    include_directories(${REVISION_EDITOR_INCLUDE_DIRECTORIES} ${REVISION_EDITOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${REVISION_EDITOR_SOURCES} ${REVISION_EDITOR_MAIN_SOURCES})
    include_directories(${REVISION_EDITOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)