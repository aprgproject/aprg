cmake_minimum_required(VERSION 3.16)

# Set project details
project(FileDestructor C CXX)
set(OUTFILE ${PROJECT_NAME})
set(FILE_DESTRUCTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${FILE_DESTRUCTOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${FILE_DESTRUCTOR_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
if (APRG_TEST_MODE)
    add_executable(${OUTFILE} ${FILE_DESTRUCTOR_SOURCES_AND_TESTS})
    include_directories(${FILE_DESTRUCTOR_INCLUDE_DIRECTORIES} ${FILE_DESTRUCTOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${FILE_DESTRUCTOR_SOURCES} ${FILE_DESTRUCTOR_MAIN_SOURCES})
    include_directories(${FILE_DESTRUCTOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
