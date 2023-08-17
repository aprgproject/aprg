/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Process Management Service API header file
* @module                AaPro
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAPRO_H_
#define _MCU_RT_IFAAPRO_H_

#include <CcsCommon.h>

#include <../../SHARED/MCU_RT/Definitions/IfAaPro_Defs.h>
#include <../../SHARED/MCU_RT/Messages/IfAaPro_Msg.h>
#include <../../COMMON/Definitions/IfAaPro_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup dgAaProApiLinux AaPro LINUX API
*@ingroup dgAaPro
*
* Application Programming Interface.
*
* API specification (current): https://sharenet-ims.inside.nokiasiemensnetworks.com/livelink/livelink?func=ll&objId=396832787&objAction=Browse
*
*@{*/


/**
*******************************************************************************
*
*   @brief      Installs exit handler for calling EU.
*
*   @param[in]  exitHandler     pointer to exit handler
*   @param[in]  arguments       pointer to arguments which will be passed to exit handler when it is called
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function installs exit handler for calling EU.
*   Exit handler will be executed before EU terminates.
*
*   @par Errors:
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed during exit handler creation.
*        E.g memory allocation failure
*      - #EAaProEuRetVal_InvalidValue if pointer to exit handler is null.
*
*   @par Restrictions:
*   This function is used on MCU Linux target only.
*
*   @par Example:
*
*   @code
*   #include <IfAaPro.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaProEuCreateAndStartWithPolicy
*         &euId,
*         "exampleEu",                          // EU name
*         exampleEuStart                        // Start function
*         2048,                                 // Stack size
*         EAaProEuSchedulingPolicy_Background,  // Scheduling policy
*         EU_PRIORITY_05,                       // Priority
*         0,                                    // nice level
*         (void*)param,
*         sizeof(strlen(param)+1),
*         GLO_FALSE);
*
*
*   void myExitHandler(void* eharg)
*   {
*      char* param = (char*)eharg;
*      // do something usefull here
*   }
*
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     char* param = (char*)arguments;
*     printf("%s\n", param);
*
*     char* eharg = "example argument";
*     EAaProEuRetVal ehRet = AaProEuInstallExitHandler(myExitHandler, (void*)eharg);
*     // check ehRet and handle appropriately
*
*     u32* ret = AaMemMalloc(sizeof(u32)); // Return value must be dynamically allocated
*
*     // code
*
*     *ret = 0x1234;
*
*     return (void*)ret;
*   }
*
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*
******************************************************************************/
EAaProEuRetVal AaProEuInstallExitHandler(TAaProEuExitHandler *exitHandler, void* arguments);


/**
*******************************************************************************
*
*   @brief Set the user Id of the EE (LINUX only)
*
*   @param[in]  userNamePtr     A pointer to the name of the user.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*
*   @par Description:
*   This function set the user ID for the current EE.
*
*   @par Errors:
*   If error occurs the  value #EAaProEuRetVal_Error is returned.
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to set the user ID for the current EE.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   EAaProEuRetVal ret  = AaProEeSetUid("toor4nsn");
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProCmdExec
*
******************************************************************************/
EAaProEuRetVal AaProEeSetUid(char* userNamePtr);

/**
*******************************************************************************
*
*   @brief Set the user Id, group Id and capabilities of the EE (LINUX only, supported only by RCP CC&S)
*
*   @param[in]  userNamePtr     A pointer to the name of the user (groupname should same as the username).
*   @param[in]  capListPtr      A pointer to the capability list.
*   @param[in]  capNum          Number of capability list members.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*
*   @par Description:
*   This function set the user Id, group Id and capabilities of the EE.
*   If don't want to set capability, just set capListPtr = GLO_NULL and capNum = 0
*
*   @par Errors:
*   If error occurs the value #EAaProEuRetVal_Error is returned.
*
*   @par Restrictions:
*   LINUX only, supported only by RCP CC&S.
*
*   @par Example:
*   Following example shows how to set the user ID, group ID and capabilities for the current EE.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   #with capabilities
*   int caps[] = { 1, 2, 3 };
*   EAaProEuRetVal ret = AaProEeSetUidAndGidWithCap("toor4nsn", (const int*)caps, 3);
*
*   #without capability
*   EAaProEuRetVal ret = AaProEeSetUidAndGidWithCap("toor4nsn", GLO_NULL, 0);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProCmdExec
*
******************************************************************************/
EAaProEuRetVal AaProEeSetUidAndGidWithCap(const char* userNamePtr, const int* capListPtr, int capNum);

/**
*******************************************************************************
*
*   @brief Function to enable/disable automatic resets (e.g. watchdog, kernel panic) on FCTE
*
*   @param[in]  srStatus     self reset status.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*
*   @par Description:
*   This function enables or disables certain features that can cause a self reset (like reset on kernel panic or
*   watchdog reset). This function is only useful on the FCTE and will return an error if
*   called on any other board.
*
*   @par Errors:
*   If error occurs the  value #EAaProEuRetVal_Error is returned.
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to enable/disable auto reset.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   EAaProEuRetVal ret  = AaProSelfResetEnable(EAaProSelfReset_Enabled);
*   // EAaProEuRetVal ret  = AaProSelfResetEnable(EAaProSelfReset_Disabled); // to disable auto reset
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
EAaProEuRetVal AaProSelfResetEnable(EAaProSelfResetStatus srStatus);

/**
*******************************************************************************
*
*   @brief Function to check if euId is valid
*
*   @param[in]  euId     euId to be checked.
*
*   @return GLO_TRUE - euId is valid
*   @return GLO_FALSE - euId is not valid
*
*   @par Description:
*   This function checks if euId value is valid
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to check euId.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   if (AaProEuIsEuIdValid(euId)) {
*   // do something usefull
*   }
*   else {
*   // handle error
*   }
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
TBoolean AaProEuIsEuIdValid(u32 euId);

/**
*******************************************************************************
*
*   @brief Function to to bind eu to certain CPU/Core
*   @param[in]  euId             euId of the EU.
*   @param[in]  numberOfCpus     total number of CPUs/Cores to which to bind given EU.
*   @param[in]  cpuSet           pointer to array of integers which contains CPU numbers, starting from 0.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_NotSupported
*   @return EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function binds eu to given number of CPUs/Cores
*
*   @par Errors:
*   If error occurs the  value #EAaProEuRetVal_Error is returned.
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to bind eu to given number of CPU Cores.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   EAaProEuRetVal ret;
*
*   //binds euId to core 0
*   int cpuSet[1] = {0};
*   ret = AaProEuSetAffinity(euId, 1, cpuSet);
*   // check ret afterwards
*
*   //binds euId to cores 2, 4, 6
*   int cpuSet[3] = {2, 4, 6};
*   ret = AaProEuSetAffinity(euId, 3, cpuSet);
*   // check ret afterwards
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
EAaProEuRetVal AaProEuSetAffinity(u32 euId, int numberOfCpus, int* cpuSet);

/**
*******************************************************************************
*
*   @brief Function to initialize AaPro Cpu load logging
*
*   @return TAaProMeasurementIdType - id of a measurement
*   @return EAaProMeasurementIdType_InvalidValue in case of error
*
*   @par Description:
*   This function initializes AaPro Cpu Load logging. It has to be called before AaProCpuLoadLogGetData.
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to get Cpu Load data.
*
*   @code
*
*   #include <IfAaPro.h>
*
*   TAaProMeasurementIdType mId = AaProCpuLoadLogInit();
*   // here you should check if returned mId is valid, and if it is not handle error
*   // start timer
*   // when timer expires                                           // these three steps
*   SAaProCpuLoadData data = AaProCpuLoadLogGetData(mId);           // can be repeated as many times
*   if (data.measurementId != EAaProMeasurementIdType_InvalidValue) // as necessary
*   {
*      // do semething usefool with data
*   }
*   else
*   {
*      // report error
*   }
*   AaProCpuLoadLogTerminate (mId);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
TAaProMeasurementIdType AaProCpuLoadLogInit(void);

/**
*******************************************************************************
*
*   @brief Function to fetch AaPro Cpu load data
*
*   @param[in]  id     id of Cpu load measurement, returned by AaProCpuLoadLogInit.
*
*   @return SAaProCpuLoadData - structure containing Cpu load data
*   @return SAaProCpuLoadData with SAaProCpuLoadData.measurementId = EAaProMeasurementIdType_InvalidValue - in case of error
*
*   @par Description:
*   This function fetches AaPro Cpu load data. AaProCpuLoadLogInit has to be called before first use of this function.
*   After data is returned measurementId inside SAaProCpuLoadData should be checked, to see if data is valid (see example).
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to get Cpu Load data.
*
*   @code
*   see example for AaProCpuLoadLogInit()
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
SAaProCpuLoadData AaProCpuLoadLogGetData(TAaProMeasurementIdType id);

/**
*******************************************************************************
*
*   @brief Function to terminate AaPro Cpu load logging
*
*   @param[in]  id     id of Cpu load measurement, returned by AaProCpuLoadLogInit.
*
*   @return void
*
*   @par Description:
*   This function terminates AaPro Cpu load logging. It has to be called only if running CPU load measurement is not needed any more.
*
*   @par Restrictions:
*   LINUX only.
*
*   @par Example:
*   Following example shows how to get Cpu Load data.
*
*   @code
*   see example for AaProCpuLoadLogInit()
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see N/A
*
******************************************************************************/
void AaProCpuLoadLogTerminate(TAaProMeasurementIdType id);

/**
*******************************************************************************
*
*   @brief   Executes a command without using bash and logger and blocks until the command terminates.
*
*
*   @param[in]  command  Name of the command to execute with the OS/POSIX absolute path.
*   @param[in]  args     Arguments given to command prior to execution or GLO_NULL
*   @param[in]  flags    Flags to further control execution of the process, e.g.
*                        report process exit in the node status.
*   @param[out] retVal   Pointer to placeholder for return value from
*                        the executed command or GLO_NULL.
*                        AaPro is not modifying retVal, so it is user responsibility
*                        to interpret the value depending on the executed command.
*
*   @return  #EAaProEuRetVal_NoError
*   @return  #EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function executes defined command and the caller of the function is blocked
*   until the command terminates. Result of the command is returned via retVal.
*   The command is invoked in the context of EE or in EU depending on the system.
*   \n\n
*   If system supports invocation of the command in context of EU, the EU shall
*   be in the context of the current EE where this function is called. If system
*   supports invoking the command in EE, a new EE is created for the command.
*   For more details see @ref dsVariation "API variation specification".
*   The EU calling this function shall always be the parent for the command EE/EU.
*   \n\n
*   By setting the flag #EAaProSupervisionFlag_NotSupervised you indictae that the
*   exit of the process shall cause no action performed by AaPro.
*   By setting the flag #EAaProSupervisionFlag_ReportExit you indictae that the
*   exit of the process shall be reported as error via the node status.
*   By setting the flag #EAaProSupervisionFlag_CriticalFailed you indictae that the
*   exit of the process shall trigger reboot.
*   Exception: On RAT containers behaviour will be the same as with #EAaProSupervisionFlag_ReportExit
*
*   @par Errors:
*   In case of invalid parameters are given via parameters (e.g. NULL pointer),
*   or the defined command is not found, #EAaProEuRetVal_InvalidValue is returned.
*   If parameters are OK and command is found but the execution of it fails or command
*   dies unexpectedly (f.e. signal), error will be reported by AaPro, and error
*   code of the command is returned via retVal.
*   For flags values AAPRO_FLAG_CMDEXEC_REPORT_EXIT and AAPRO_FLAG_CMDEXEC_CRITICAL_EE:
*   If command execution will succed, but non 0 return value will be returned by command,
*   retVal will be set to return value, and error will be reported. retVal should be interpreted
*   by user.
*   For flags value 0:
*   If command execution will succed, but non 0 return value will be returned, retVal will
*   be set to return value, but error will not be reported in AaPro. retVal should
*   be interpreted by user.
*   Othervice 0 is returned.
*   The error code is system specific.
*
*   @par Restrictions:
*   For products using systemd, setting \ref AAPRO_FLAG_CMDEXEC_CRITICAL_EE will not end in reboot if:
*   \ref AAPRO_TAG_RECOVERY_RESET is set to \c 1.
*
*   This function requires full OS/POSIX path to command. This function doesn't include
*   Bash usage, so all bash specific instructions ( '|', '>', etc.) are treated as errors.
*   To use bash specific instructions use "/bin/bash" as a command and the real command as
*   argument (see @example), or use AaProCmdExec().
*   See @ref dsVariation "API variation specification".
*
*   @par Example:
*
*   @code
*
*   //Example 1:
*   #include <IfAaPro.h>
*
*   int retval;
*   EAaProEuRetVal rc = AaProCmdExecRaw("/bin/ps", "-A", EAaProSupervisionFlag_NotSupervised, &retval); // Execute command 'ps -A'
*
*   if (rc != EAaProEuRetVal_NoError)
*   {
*      // Invalid parameter given to AaProCmdExec or command 'ps' not found
*   }
*   else if (retval != 0)
*   {
*      // Execution of 'ps -A' failed. Maybe -A is not correct parameter.
*   }
*
*   //Example 2:
*
*   #include <IfAaPro.h>
*
*   int retval;
*   EAaProEuRetVal rc = AaProCmdExecRaw("/bin/bash", "-c 'ps -A | grep AaPro > example.txt'", EAaProSupervisionFlag_NotSupervised, &retval); // Execute command 'ps -A | grep AaPro > example.txt'
*
*   if (rc != EAaProEuRetVal_NoError)
*   {
*      // Invalid parameter given to AaProCmdExec or command 'ps' not found
*   }
*   else if (retval != 0)
*   {
*      // Execution of 'ps -A' failed. Maybe -A is not correct parameter.
*   }
*
*   @endcode
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaProCmdExec()
******************************************************************************/
EAaProEuRetVal
AaProCmdExecRaw( const char* command, const char* args, EAaProSupervisionFlag flags, int* retVal );

/**
*******************************************************************************
*
*   @brief Function to query recovery type.
*
*   @return
*   Recovery type.
*
*   EAaProRecoveryType_Error means that the calling application information cannot be found.
*
*   EAaProRecoveryType_NoRecovery means that no recovery has happened.
*   Notice that no recovery only happens at VM first start stage.
*
*   @par Description:
*
*   @par Restrictions:
*   Linux only. This API will be supported only by RCP CC&S, both RCP CC&S MCU and RT will support this API.
*
*   @par Example:
*   None
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
******************************************************************************/
EAaProRecoveryType AaProGetRecoveryType(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IFAAPRO_H_*/
