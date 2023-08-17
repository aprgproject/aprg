/** @file
*   @brief AaTbts API.
*   @copyright 2014 NSN. All rights reserved.
*   @copyright 2018, 2019 Nokia. All rights reserved.
*/

#ifndef IFAATBTS_H
#define IFAATBTS_H

/************************** DOXYGEN GROUPS ************************************/

/*!
 *  @defgroup dgAaTbts  Target Based Testing Solution (AaTbts)
 *  @ingroup  dgTestabilitySw
 *
 *  Common Computer and Support SW TBTS Service.
 *
 *  TBTS Service provides uniform API for testing.
 */

/*!
 *  @defgroup dgAaTbtsApi API
 *  @ingroup  dgAaTbts
 *
 *  Application Programming Interface.
 */
/*@{*/

/************************** INCLUDED FILES ************************************/

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef CCS_LINUX
#define UNUSEDFORMATATTR __attribute__((unused))
#else
#define UNUSEDFORMATATTR
#endif

/************************** PUBLIC DECLARATIONS *******************************/

/*
 *  Forward declares
 */
struct CTbtsSubsystem_c;
struct CTbtsTestCase_c;

/*!
 *  @brief  Identifies how the test case can be deployed.
 */
typedef enum ETbtsInstanceType
{
    /*!
     *  Only one instance allowed to run at time. If another test is tried to
     *  start, it start will fail
     */
    ETbtsInstanceType_Single    = 1,
    /*! @deprecated NOT IN USE ANYMORE!
     *  THIS FUNCTIONALITY IS OBSOLETE
     *  Only one instance allowed to run at time but it is public, server style
     *  test case. New test parameters are delivered to test case
     */
    ETbtsInstanceType_Singleton = 2,
    /*!
     *  Multiple instances of same test case is allowed to run at same time
     */
    ETbtsInstanceType_Multi     = 3
}ETbtsInstanceType;

/*!
 *  @brief  Identifies test case privileges.
 */
typedef enum ETbtsProcessPrivilege
{
    /*!
     *  Process has no limits, in OSE world -> SUPER_USER process.
     */
    ETbtsProcessPrivilege_All     = 0,
    /*!
     *  Process has limited access, in OSE world -> USER process.
     */
    ETbtsProcessPrivilege_Limited = 1
}ETbtsProcessPrivilege;

/*!
 *  @todo   Reserve message id for AaTbts.
 */
#define TBTS_TEST_CONTROL_RESULT_IND_MSG 0xFF07  /* !- SIGNO(struct TbtsTestControlResultInd) -!  */
#define TBTS_STOP_TEST_IND_MSG           0xFF04  /* !- SIGNO(struct TbtsStopTestInd) -!  */
#define TBTS_TEST_PARAMETERS_IND_MSG     0xFF0F  /* !- SIGNO(struct TbtsTestParametersInd) -!  */

/*!
 *  @brief  This is used to inform controlled test result to test case which
 *          started another test.
 */
typedef struct TbtsTestControlResultInd
{
    u32             testId;     /*!< Test unique id running in target */
    TBoolean        success;    /*!< Success information of test */
    u32             dataSize;   /*!< Test extra result data in bytes */
    u32             data[1];    /*!< Test extra result data */
}TbtsTestControlResultInd;

/*!
 *  @brief  This is used to inform that the tester ordered to stop the test.
 */
typedef struct TbtsStopTestInd
{
    u32 dummy;                  /*!< Useless field for c compatibility */
}TbtsStopTestInd;

/*!
 *  @brief  This is used to indicate that singleton test receives new parameters.
 */
typedef struct TbtsTestParametersInd
{
    u32 size;                   /*!< Size of the data */
    u8  data[1];                /*!< Pointer to data */
}TbtsTestParametersInd;


/*-------------------------- SUBSYSTEM STUFF ---------------------------------*/

/**
 *  @brief      Initialize function of subsystem
 *
 *  @param[in]  SubsystemName    name of subsystem
 */
#define AATBTS_SUBSYSTEM_INITIALIZE_FUNCTION(SubsystemName) \
    static void CSubsystem##SubsystemName##_Initialize(struct CTbtsSubsystem_c* _this)

/**
 *  @brief      Declare of subsystem
 *
 *  @param[in]  SubsystemName   name of subsystem
 */
#define AATBTS_SUBSYSTEM_DECLARE(SubsystemName)                                  \
    void CSubsystem##SubsystemName##_Constructor(struct CTbtsSubsystem_c* _this) \
    {                                                                            \
        AaTbtsSubsystemBuild(_this,                                              \
                             #SubsystemName,                                     \
                             CSubsystem##SubsystemName##_Initialize);            \
    }

/**
 *  @brief      Prototype of test case
 *
 *  @param[in]  SubsystemName    name of subsystem
 */
#define AATBTS_SUBSYSTEM_PROTOTYPE(SubsystemName)    \
    /* Constructor prototype */                      \
    void CSubsystem##SubsystemName##_Constructor(struct CTbtsSubsystem_c* _this)

/**
 *  @brief      Constructor of subsystem
 *
 *  @param[in]  name    name of subsystem
 */
#define AATBTS_SUBSYSTEM(name) \
    CSubsystem##name##_Constructor

/**
 *  @brief      Constructor of test case
 *
 *  @param[in]  name            name of testcase
 */
#define AATBTS_TESTCASE(name) \
    CTest##name##_CreateInstance


/*-------------------------- TESTCASE STUFF ----------------------------------*/

/**
 *  @brief      Initialize function of test case
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_INITIALIZE_FUNCTION(TestCaseName) \
    static void CTest##TestCaseName##_Initialize(struct CTbtsTestCase_c* _this UNUSEDFORMATATTR)

/**
 *  @brief      Validate function of test case
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_VALIDATE_FUNCTION(TestCaseName) \
    static void CTest##TestCaseName##_Validate(struct CTbtsTestCase_c* _this UNUSEDFORMATATTR)

/**
 *  @brief      Perform function of test case
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_PERFORM_FUNCTION(TestCaseName) \
    static void CTest##TestCaseName##_Perform(struct CTbtsTestCase_c* _this UNUSEDFORMATATTR)

/**
 *  @brief      Declare of test case
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_DECLARE(TestCaseName) \
    void* CTest##TestCaseName##_CreateInstance(void)                         \
    {                                                                        \
        struct CTbtsTestCase_c* instancePtr = AaTbtsTestcaseAllocInstance(); \
        AaTbtsTestcaseBuild(instancePtr,                                     \
                            #TestCaseName,                                   \
                            (void (*)(struct CTbtsTestCase_c*))CTest##TestCaseName##_Validate, \
                            (void (*)(struct CTbtsTestCase_c*))CTest##TestCaseName##_Perform); \
        return instancePtr;                                                  \
    }

/**
 *  @brief      Declare of test case extend version, where user can defined
 *              test case properties.
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_DECLARE_EXT(TestCaseName) \
    void* CTest##TestCaseName##_CreateInstance(void)                         \
    {                                                                        \
        struct CTbtsTestCase_c* instancePtr = AaTbtsTestcaseAllocInstance(); \
        AaTbtsTestcaseBuild(instancePtr,                                     \
                            #TestCaseName,                                   \
                            (void (*)(struct CTbtsTestCase_c*))CTest##TestCaseName##_Validate, \
                            (void (*)(struct CTbtsTestCase_c*))CTest##TestCaseName##_Perform); \
        CTest##TestCaseName##_Initialize(instancePtr);                       \
        return instancePtr;                                                  \
    }

/**
 *  @brief      Prototype of test case
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AATBTS_TESTCASE_PROTOTYPE(TestCaseName) \
    void* CTest##TestCaseName##_CreateInstance(void)


/************************** PUBLIC INTERFACES *********************************/

/*!
 *  @name   Service
 */
/*@{*/
/**
 *  @brief      Functions for initialize AaTbts with AaConfig and AaStartup.
 */
void AaTbtsInitCe(void);
void AaTbtsInitEe(void);

/**
 *  @brief      Function for initialize target based testing solution service
 *
 *  @param[in]  processPriority    priority of service process
 *
 *  @return     Service process id, zero is returned if fails.
 */
u32 AaTbtsServiceInitialize(u32 processPriority) CCS_DEPRECATED("Please do not use it anymore. This functionality is obsolete.");

/**
 *  @brief      Function for register subsytem to service
 *
 *  @param[in]  constructorFunctionPtr    pointer to
 */
void AaTbtsServiceRegisterSubsystem(void(*constructorFunctionPtr)(struct CTbtsSubsystem_c*));

/**@}*/

/*!
 *  @name   Subsystem
 */
/*@{*/
/**
 *  @brief      Function for build subsystem instance
 *
 *  @param[in]  _this                   pointer to current subsystem instance
 *  @param[in]  subsystemNameStringPtr  pointer to subsystem name
 *  @param[in]  initializeFunctionPtr   pointer function which initializes the subsystem
 *
 *  @note       this function is hided inside AATBTS_SUBSYSTEM_DECLARE define
 */
void AaTbtsSubsystemBuild(struct CTbtsSubsystem_c* _this,
                          char* subsystemNameStringPtr,
                          void (*initializeFunctionPtr)(struct CTbtsSubsystem_c*));

/**
 *  @brief      Set subsytem brief
 *
 *  @param[in]  brief   brief of subsystem
 */
#define AaTbtsSubsystemSetBrief(brief) \
    AaTbtsSubsystemSetBrief2(_this, brief)

/**
 *  @brief      Add test case to subsystem
 *
 *  @param[in]  TestCaseName    name of test case
 */
#define AaTbtsSubsystemAddTestCase(testcase) \
    AaTbtsSubsystemAddTestCase2(_this, testcase)

/**
 *  @brief      Function for set subsystem brief
 *
 *  @param[in]  _this    pointer to current test case instance
 *  @param[in]  brief    brief text
 */
void AaTbtsSubsystemSetBrief2(struct CTbtsSubsystem_c* _this, char* brief);

/**
 *  @brief      Function for add test case to subsystem
 *
 *  @param[in]  _this                      pointer to current test case instance
 *  @param[in]  createInstanceFunctionPtr  pointer to instance creator function
 */
void AaTbtsSubsystemAddTestCase2(struct CTbtsSubsystem_c* _this,
                                 void*(*createInstanceFunctionPtr)(void));

/**@}*/

/*!
 *  @name   Testcase
 */
/*@{*/
/**
 *  @brief  Build test case
 *
 *  @return pointer to test parameters
 *
 *  @note   this is hided inside AATBTS_TESTCASE_DECLARE define
 */
void AaTbtsTestcaseBuild(struct CTbtsTestCase_c* _this,
                         const char* testNameStringPtr,
                         void (*validateFunctionPtr)(struct CTbtsTestCase_c*),
                         void (*performFunctionPtr)(struct CTbtsTestCase_c*));

/**
 *  @brief  Alloc new test case instance
 *
 *  @return pointer to test case instance
 *
 *  @note   this is hided inside AATBTS_TESTCASE_DECLARE define
 */
struct CTbtsTestCase_c* AaTbtsTestcaseAllocInstance(void);

/**
 *  @brief  Get test case parameters pointer
 *
 *  @return pointer to test parameters
 */
void* AaTbtsTestcaseGetParametersPtr(void);

/**
 *  @brief      Get test case parameters size
 *
 *  @return size of test parameters
 */
u32 AaTbtsTestcaseGetParametersSize(void);

/**
 *  @brief      Set test case validate status
 *
 *  @param[in]  status    success info of test input parameters
 */
void AaTbtsTestcaseSetValidateStatus(TBoolean status);

/**
 *  @brief      Set test case result status
 *
 *  @param[in]  status    success of test
 */
void AaTbtsTestcaseSetResultStatus(TBoolean status);

/**
 *  @brief  Set test case extra result data
 *
 *  @param[in]  size    size of extra data
 *  @param[in]  ptr     pointer to extra data
 */
void AaTbtsTestcaseSetResultData(u32 size, void* ptr);

/**
 *  @brief      Print flow trace of test case
 *
 *  @param[in]  format    unformatted string pointer
 *  @param[in]  ...       variable argument data for formatting string
 */
void AaTbtsTestcaseTracePrint(const char* format, ...);

/**
 *  @brief      Inform complete status of test case
 *
 *  @param[in]  percent    complete status in percent
 */
void AaTbtsTestcaseTraceComplete(u32 percent);

/**
 *  @brief      Print memory dump trace from test case.
 *
 *  @param[in]  memorySize    Size of the memory to be printed
 *  @param[in]  memoryPtr     Pointer to memory
 */
void AaTbtsTestcaseTraceDump(u32   memorySize,
                             void* memoryPtr);

/**
 *  @brief      Query own SIC address
 *
 *  @return     test case SIC address
 *
 *  @note       This is only hack because syscom it not ready
 */
u32 AaTbtsTestcaseGetSicAddress(void);

/**
 *  @brief      Set test case name
 *
 *  @param[in]  testcaseName    name of test case
 */
void AaTbtsTestcaseSetName(char* testcaseName);


#define AaTbtsTestcaseSetBrief(brief) \
    AaTbtsTestcaseSetBrief2(_this, brief)
/**
 *  @brief      Set test case brief
 *
 *  @param[in]  _this    pointer to current instance
 *  @param[in]  brief    pointer to test case brief
 */
void AaTbtsTestcaseSetBrief2(struct CTbtsTestCase_c* _this, char* brief);


#define AaTbtsTestcaseSetInstanceType(instanceType) \
    AaTbtsTestcaseSetInstanceType2(_this, instanceType)
/**
 *  @brief      Set test case instance type
 *
 *  @param[in]  _this           pointer to current instance
 *  @param[in]  instanceType    instance type
 */
void AaTbtsTestcaseSetInstanceType2(struct CTbtsTestCase_c* _this,
                                    ETbtsInstanceType instanceType);


#define AaTbtsTestcaseSetProcessProperties(priority, privilege) \
    AaTbtsTestcaseSetProcessProperties2(_this, priority, privilege)
/**
 *  @brief      Set test case process properties
 *
 *  @param[in]  _this        pointer to current instance
 *  @param[in]  priority     priority test process
 *  @param[in]  privilege    prilege of test process
 */
void AaTbtsTestcaseSetProcessProperties2(struct CTbtsTestCase_c* _this,
                                         u32 priority,
                                         ETbtsProcessPrivilege privilege);

/**
 *  @brief      Function for start another test case
 *
 *  @param[in]  tbtsServiceAddress  Address of TBTS service where test is started
 *  @param[in]  subsystemNamePtr    Subsystem name to where test is registered
 *  @param[in]  testcaseNamePtr     Testcase name to be started
 *  @param[in]  parametersSize      Size of parameter given to test case
 *  @param[in]  parametersPtr       Pointer to parameter data
 *
 *  @return     test id, if zero test start failed.
 *
 *  @note       - User does not need handle test stopping, framework will
 *                handle it.
 *              - When test is finished, test case need handle asynchronous
 *                result indication message:
 *                message id = TBTS_TEST_CONTROL_RESULT_IND_MSG,
 *                message structure = TbtsTestControlResultInd.
 */
u32 AaTbtsTestControlStart(u32 tbtsServiceAddress,
                           const char* subsystemNamePtr,
                           const char* testcaseNamePtr,
                           u32 parametersSize,
                           void* parametersPtr);

/**
 *  @brief      Function for stop another test case
 *
 *  @param[in]  testId    test case to be stopped
 */
void AaTbtsTestControlStop(u32 testId);

/**@}*/

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* IFAATBTS_H */
