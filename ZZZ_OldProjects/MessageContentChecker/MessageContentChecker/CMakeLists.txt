cmake_minimum_required(VERSION 3.16)

# Set project details
project(MessageContentChecker C CXX)
set(OUTFILE ${PROJECT_NAME})
set(MESSAGE_CONTENT_CHECKER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set TEST_MODE to ON to enable tests and OFF to call main function.
option(TEST_MODE "Enable test mode" ON)

# Locate APRG Directory first because its used on other cmakes
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Process for files, directories and flags
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/FindFilesAndDirectories.cmake)
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/AddFlags.cmake)

#Assign Sack Directory
set(SackDirectory "F:/Branches/ControlPlane/sbts1/tcom")

set(SACKS_DIR_TO_INCLUDE
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Temp
    ${SackDirectory}/I_Interface/Global_Env/Definitions
    ${SackDirectory}/I_Interface/Global_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env
    ${SackDirectory}/I_Interface/Application_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Interfaces
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Messages
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Definitions
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/ServiceInterface
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/ServiceInterface
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/DSP/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/Messages
    ${SackDirectory}/I_Interface/Platform_Env/MCUHWAPI_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/MCUHWAPI_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/DSPHWAPI_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/DSPHWAPI_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSPHWAPI_ENV/FARADAY_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/Definitions
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES_AND_TESTS})
    include_directories(${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${MESSAGE_CONTENT_CHECKER_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES} ${MESSAGE_CONTENT_CHECKER_MAIN_SOURCES})
    include_directories(${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
