cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgWebCrawler C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_WEB_CRAWLER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_WEB_CRAWLER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

#Assign specific definitions
add_definitions(-DAPRG_WEB_CRAWLER_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/configuration.txt")
add_definitions(-DAPRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/firefoxConfiguration.txt")
add_definitions(-DAPRG_CRAWLER_TEST_DIRECTORY="${APRG_DIR}AprgWebCrawler/TestDirectory")
add_definitions(-DAPRG_CRAWLER_TEST_TEMPORARY_FILE_PATH="${APRG_DIR}AprgWebCrawler/TemporaryFile/temp.txt")
add_definitions(-DAPRG_WEB_CRAWLER_FIX_BATCH_FILE="${APRG_DIR}AprgWebCrawler/fixDirectoryNames.bat")

# Include other projects
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/CurlCpp/AprgCmakeInclude/CurlCpp.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCmakeInclude/AprgLocalUserAutomation.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_WEB_CRAWLER_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_WEB_CRAWLER_SOURCES})
include_directories(${APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_CURL_CPP APRG_LOCAL_USER_AUTOMATION APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
