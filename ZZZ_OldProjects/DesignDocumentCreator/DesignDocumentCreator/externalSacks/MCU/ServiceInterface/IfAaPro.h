/** @file
*   @brief AaPro MCU function prototypes
*   @copyright 2017, 2019 Nokia. All rights reserved.
*/
#ifndef _MCU_IFAAPRO_H_
#define _MCU_IFAAPRO_H_

#include <glo_def.h>
#include "CcsCommon.h"

#include <../../COMMON/ServiceInterface/IfAaPro.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaPro.h>
#include <../../MCU/Definitions/IfAaPro_Defs.h>
#include <../../MCU/Messages/IfAaPro_Msg.h>
#include <../../COMMON/Definitions/IfAaSysTime_Defs.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup dgAaProApiMcu AaPro MCU API
*@ingroup dgAaPro
*
* Application Programming Interface.
*
* API specification (current): https://sharenet-ims.inside.nokiasiemensnetworks.com/livelink/livelink?func=ll&objId=396832787&objAction=Browse
*
*/


/**
*******************************************************************************
*
*   @brief      Returns the system ID (pthread_t) of the own EU (LINUX only).
*
*   @return     system ID
*
*   @par Description:
*   This function returns the system ID of the own EU. ID is unique inside CE.
*
*   @par Errors:
*   Raises a fatal exception if called on non-supported platforms using AaPro "posix" mode.
*
*   @par Restrictions:
*   This API is only released for use by TRSW (to enable usage of pthread_self()) and
*   OAM MT/SCT test environments. Use of other POSIX APIs (pthread_cancel,kill,join) is
*   at own risk i.e. conflicts with CC&S AaPro are possible. If thread cancellation,join,kill
*   support is needed officially a CN should be raised. The build which support this API are
*   LINUX_PC,LINUX_PC64,LINUX_KEPLER2 (FZM) and LINUX_OCTEON2_LRC (LRC).
*
*   @par Example:
*   Following example shows how to get the system ID of the own EU
*
*   @code
*
*   #include <IfAaPro.h>
*
*   phtread_t threadId = AaProEuGetSystemId();
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
*   @see AaProEuCreateAndStart
*
******************************************************************************/
#include <pthread.h>
pthread_t AaProEuGetSystemId(u32 euId);

/**
*******************************************************************************
*
*   @brief      Creates and starts a joinable prioritized execution unit with scheduling policy.
*               Eu may be joined with function AaProEuWaitForEu.
*
*   @param[out] euIdPtr       Pointer to the variable where ID of the created Eu will be stored.
*   @param[in]  euNamePtr     A pointer to the name of the Eu.
*   @param[in]  euEntryPoint  The address where the Eu should begin execution. Portable programs
*                             should define the entrypoint with the AAEU_PROCESS macro.
*   @param[in]  euStackSize   Specifies the size (in bytes) of the stack.
*   @param[in]  euPolicy      Scheduling policy for the Eu.
*   @param[in]  euPriority    The priority level for the realtime Eu.
*   @param[in]  euNiceness    The nice level for the background Eu.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new Eu.
*   @param[in]  sizeOfEuArg   Size of the argument (in bytes) to forward to Eu.
*
*   @return #EAaProEuRetVal_NoError on success, apropriate errror in case of failure.
*
*   @par Description:
*   This function creates and starts a prioritized execution unit as a real-time or background
*   process.
*   In case (sizeOfEuArg > 0):
*   Changes in #euArgPtr causes no effect to the created Eu after creation, because
*   AaProEuCreateAndStart() family of functions copy #euArgPtr.
*   In case (sizeOfEuArg == 0):
*   Modification of the memory where #euArgPtr is pointing to does have effect to the created Eu
*   after creation, because AaProEuCreateAndStart() family of functions passes the #euArgPtr
*   directly to the pthread. The user is responsible for freeing the memory to which #euArgPtr
*   refers.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself handles the error, if
*   maximum number of concurrent Eus are exceeded.
*
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed when new Eu created, e.g memory allocation
*        failure.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_OutOfResources if maximum number of Eus would be exceeded.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to create and start execution unit
*
*   @code
*   // example 1 - with argument copy (sizeOfEuArg > 0)
*
*   #include <IfAaPro.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   const char* param = "something";
*
*   ret = AaProEuCreateAndStartExternalJoin(
*         &euId,
*         "exampleEu",                          // Eu name
*         exampleEuStart                        // Start function
*         2048,                                 // Stack size
*         EAaProEuSchedulingPolicy_Background,  // Scheduling policy
*         EU_PRIORITY_05,                       // Priority
*         0,                                    // nice level
*         (void*)param,
*         sizeof(char)*(strlen(param)+1),
*         GLO_FALSE);
*
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     char* param = (char*)arguments;
*     printf("%s\n", param);
*     u32* ret = AaMemMalloc(sizeof(u32)); // Return value must be dynamically allocated
*
*     // code
*
*     *ret = 0x1234;
*
*     return (void*)ret;
*   }
*
*   // example 2 - no argument copy (sizeOfEuArg == 0)
*
*   #include <IfAaPro.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   const char* param = "something";
*
*   ret = AaProEuCreateAndStartExternalJoin
*         &euId,
*         "exampleEu",                          // Eu name
*         exampleEuStart                        // Start function
*         2048,                                 // Stack size
*         EAaProEuSchedulingPolicy_Background,  // Scheduling policy
*         EU_PRIORITY_05,                       // Priority
*         0,                                    // nice level
*         (void*)param,
*         0,                                    // no arg copy, pass pointer directly
*         GLO_FALSE);
*
*   // do not free param until the thread has finished!
*
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     const char* param = (const char*)arguments;
*     printf("%s\n", param);
*     u32* ret = AaMemMalloc(sizeof(u32)); // Return value must be dynamically allocated
*
*     // code
*
*     *ret = 0x1234;
*
*     return (void*)ret;
*   }
*   @endcode
*
*   @par Usage:
*   Macro #AAPRO_GET_EU_ARGS can be used to get pointer to the Eu arguments in the context of the
*   new Eu. See example.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCurrent, AaProEuWaitForEu, AaProEuCheckJoinable
*
******************************************************************************/
EAaProEuRetVal AaProEuCreateAndStartExternalJoin(u32                      *euIdPtr,
                                                 const char               *euNamePtr,
                                                 TAaProEuEntryPoint       *euEntryPoint,
                                                 u32                      euStackSize,
                                                 EAaProEuSchedulingPolicy euPolicy,
                                                 u32                      euPriority,
                                                 i32                      euNiceness,
                                                 void                     *euArgPtr,
                                                 u32                      sizeOfEuArg);


/**
*******************************************************************************
*
*   @brief      Interface for external join Eu.
*
*   @param[in]  euId             EuId to wait for.
*   @param[in]  milliseconds     Max time to wait for Eu in milliseconds.
*                                If the value is AAPRO_EU_WAIT_INFINITE, function will wait for Eu
*                                untill it will end.
*
*   @return     0 for success, on error it returns an error number.
*
*   @par Description:
*   This function allows to join Eu, which is started as joinable with
*   AaProEuCreateAndStartExternalJoin function. It allows to wait infinite time, or to set wait
*   treshold in milliseconds.
*
*   @par Errors:
*   On failure, apropriate errno defined in POSIX will be set and returned:
*       - EDEADLK     A deadlock was detected (e.g., two threads tried to join with each other); or
*                     thread specifies the calling thread.
*       - EINVAL      Thread is not a joinable thread.
*       - EINVAL      Another thread is already waiting to join with this thread.
*       - ESRCH       No thread with the ID thread could be found.
*
*   @par Restrictions:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCreateAndStartExternalJoin, AaProEuCheckJoinable
*
******************************************************************************/
int AaProEuWaitForEu(u32 euId, TAaMilliSecond milliseconds);


/**
*******************************************************************************
*
*   @brief      Check if Eu can be joined with AaProEuWaitForEu()
*
*   @param[in] euId             EuId to check.
*
*   @return     GLO_TRUE for joinable Eu, GLO_FALSE for not joinable Eu
*
*   @par Description:
*   This function allows to check, if Eu can be joined with AaProEuWaitForEu().
*
*   @par Errors:
*   No errors defined.
*
*   @par Restrictions:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCreateAndStartExternalJoin, AaProEuWaitForEu
*
******************************************************************************/
TBoolean AaProEuCheckJoinable(u32 euId);

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IFAAPRO_H_*/
