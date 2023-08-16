cmake_minimum_required(VERSION 3.16)

# Set project details
project(DesignDocumentCreator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(DD_CREATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${DD_CREATOR_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Assign specific definitions
add_definitions(-DCCS_BIG_ENDIAN)

#Assign DesignDocumentCreatorDirectory
set(DesignDocumentCreatorDirectory ${CMAKE_CURRENT_SOURCE_DIR})

# Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${DD_CREATOR_DIR}/cmake/CommonFilesAndDirectories.cmake)
include(${DD_CREATOR_DIR}/cmake/AddFlags.cmake)

# Feature include
set(FEATURE_FOLDER "CNI21985")
include(${DD_CREATOR_DIR}/cmake/FeatureFilesAndDirectories.cmake)
add_definitions(-DLOG_LOCATION="${DD_CREATOR_DIR}/../DesignDocumentCreatorLogs")

# Assign Sack Directory
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

set(TCOM_PRIVATE_SACK_DIRECTORY ${SackDirectory}/I_Interface)
PRINT_STATUS("Looking for TCOM_PRIVATE_SACKS C/C++ files in: [${TCOM_PRIVATE_SACK_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(TCOM_PRIVATE_SACKS TCOM_PRIVATE_SACK_DIRECTORY)

set(BTS_SACK_DIRECTORY ${SackDirectory}/I_Interface)
PRINT_STATUS("Looking for BTS_SACKS C/C++ files in: [${BTS_SACK_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(BTS_SACKS BTS_SACK_DIRECTORY)

set(DD_CREATOR_INCLUDE_DIRECTORIES ${DD_CREATOR_DIR}/src ${DD_CREATOR_DIR}/tst)

# Do final steps
add_executable(${OUTFILE} ${DD_CREATOR_COMMON_SOURCES_AND_TESTS} ${FEATURE_SOURCES_AND_TESTS} ${TCOM_PRIVATE_SACKS} ${BTS_SACKS})
include_directories(
    ${FEATURE_INCLUDE_DIRECTORIES}
    ${DD_CREATOR_INCLUDE_DIRECTORIES}
    ${SACKS_DIR_TO_INCLUDE}
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION bin)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
