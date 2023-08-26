cmake_minimum_required(VERSION 3.16)

# Set project details
project(CurlCpp)
set(OUTFILE ${PROJECT_NAME})
set(APRG_CURL_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_CURL_CPP_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Add MacPorts
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
endif()

# Include other projects
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/ZZZ_OldProjects/curl/AprgCMakeToInclude/Curl.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_CURL_CPP_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_CURL_CPP_SOURCES_AND_TESTS})
include_directories(${APRG_CURL_CPP_INCLUDE_DIRECTORIES} ${APRG_CURL_CPP_TEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} ${CURL_LIBRARIES_TO_LINK} wsock32 ws2_32 APRG_COMMON)
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
