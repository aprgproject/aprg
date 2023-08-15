cmake_minimum_required(VERSION 3.16)
project(HeartTee C CXX)

# Set project details
set(OUTFILE ${PROJECT_NAME})
set(HEART_TEE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

# Locate APRG Directory first because its used on other cmakes
include(${HEART_TEE_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

# Process for files, directories and flags
include(${HEART_TEE_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${HEART_TEE_DIR}/cmake/AddFlags.cmake)

set(SPECIAL_INCLUDE_DIRECTORIES
    src/HeartTee
    src/SerialPort
    src/SqlConnect
    src/Fourier
)

# Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES_AND_TESTS})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${HEART_TEE_TEST_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} mysqlclient ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES} ${HEART_TEE_MAIN_SOURCES})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} mysqlclient)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
