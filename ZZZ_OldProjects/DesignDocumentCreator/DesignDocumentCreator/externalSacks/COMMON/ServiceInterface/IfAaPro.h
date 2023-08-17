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
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IFAAPRO_H_
#define _COMMON_IFAAPRO_H_

#include <CcsCommon.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaPro_Defs.h>
#endif
/*----------------------- DOXYGEN GROUPS ------------------------------------*/

/**
*@defgroup dgAaPro Process Management Service (AaPro)
*@ingroup dgBasicComputingSw
*
* AaPro Wiki: http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaPro
*
*/

/**
* @defgroup dpAaProRdParams R&D parameters
* @ingroup dgAaPro
*
* R&D parameters are used for fast runtime variability when execution performance
* is critical and the data must be able to accessed fast. As @ref dsVariation "configuration tags",
* R&D parameters can be used for capability and state advertisement too. The parameters
* has fixed size key and data which may limit their usage. Memory addresses cannot be transferred
* portable way using R&D parameters.
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Tag name:        ERadCcs_PrintAaPro
*
*  Direction:       input
*
*  Description:     Parameter for controlling debug print-outs of AaPro.
*
*  Effect analysis: Enables or disabled Debug severity level printouts.
*
*  Restriction:     None
*
*  Value:           Range:       Description:
*                   0            Debug severity printouts disabled
*                   1            Debug severity printouts enabled
*
*  Text:            AaPro
*
*  See:             None
* @endverbatim
*
*/

/**
* @defgroup dpAaProErrors Exception codes
* @ingroup dgAaPro
*
* Exception codes are used with Error Management Service (AaError) and they describe
* various error situations a service may have and report. Important part of exception
* is the severity. Usually it is non-fatal thus execution of application continues
* after the exception reporting but in some special case execution is prohibited and
* the application is eventually terminated.
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Error code:       EAaErrorCcs_AaPro_InvalidParam
*
*  Severity:         Non-fatal
*
*  Description:      Invalid parameter has been given.
*
*  Extra code:       None
*
*  Recovery actions: Using of correct parameters.
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaPro_MemAllocFailure
*
*  Severity:         Non-fatal
*
*  Description:      Dynamic memory allocation failed. Probably due to resource sortage.
*
*  Extra code:       None
*
*  Recovery actions: Try again later.
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaPro_EuCreationFailed
*
*  Severity:         Non-fatal
*
*  Description:      EU creation failed for some reason. Probably resource shortage.
*
*  Extra code:       None
*
*  Recovery actions: Try again later.
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaPro_UnexpectedMessage
*
*  Severity:         Non-fatal
*
*  Description:      Reveiced internal message but the message was unexpected.
*                    Possible internal implementation error.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
*/

/*----------------------- INCLUDED FILES ------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif



/**
*@defgroup dgAaProApiCommon AaPro COMMON API
*@ingroup dgAaPro
*
* Application Programming Interface.
*
* API specification (current): https://sharenet-ims.inside.nokiasiemensnetworks.com/livelink/livelink?func=ll&objId=396832787&objAction=Browse
*
*@{*/


/*----------------------- PUBLIC DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
*******************************************************************************
*
*   @brief      Creates and starts a priorized execution unit
*
*   @param[out] euIdPtr       Pointer to the variable where ID of the created
*                             EU stored.
*   @param[in]  euNamePtr     A pointer to the name of the EU.
*   @param[in]  euEntryPoint  The address where the EU should begin execution
*                             Portable programs should define the entrypoint
*                             with the AAEU_PROCESS macro.
*   @param[in]  euStackSize   Specifies the size (in bytes) of the stack.
*   @param[in]  euPriority    The priority level for the EU.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new EU.
*   @param[in]  sizeOfeuArg   Size of the argument (in bytes) to forward to
*                             EU.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*   This function creates and starts a priorized execution unit. Changes in
*   #euArgPtr causes no effect to the created Eu after creation, because
*   AaProEuCreateAndStart() function copy #euArgPtr.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_OutOfResources if maximum number of EUs would be
*        exceeded
*
*   @par Restrictions:
*   This API function does not support configurability of scheduling options.
*   Rationale for this is that scheduling options can be made configurable in
*   compile time (e.g. via header files), runtime configurability is not
*   required. Also this will keep the API simpler and application SW using
*   the API will be portable (scheduling options may differ among OSs).
*
*   @par Example:
*   Following example shows how to create and start execution unit
*
*   @code
*
*   #include <IfAaPro.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaProEuCreateAndStart
*         &euId,
*         "exampleEu",       // EU name
*         exampleEuStart     // Start function
*         2048,              // Stack size
*         EU_PRIORITY_05,    // Priority
*         (void*)&param,
*         sizeof(param));
*
*
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     u32* ret = AaMemMalloc(sizeof(u32)); // Return value must be dynamically allocated
*
*     // code
*
*     *ret = 0x1234;
*
*     return (void*)ret;
*   }
*
*   @endcode
*
*   @par Usage:
*   Macro #AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
*   in the context of the new EU. See example.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCurrent
*
******************************************************************************/
EAaProEuRetVal
AaProEuCreateAndStart( u32*                 euIdPtr,
                       const char          *euNamePtr,
                       TAaProEuEntryPoint  *euEntryPoint,
                       u32                  euStackSize,
                       u32                  euPriority,
                       void*                euArgPtr,
                       u32                  sizeOfeuArg );


/**
*******************************************************************************
*
*   @brief      Creates and starts a priorized execution unit with scheduling
*               policy.
*
*   @param[out] euIdPtr       Pointer to the variable where ID of the created
*                             EU stored.
*   @param[in]  euNamePtr     A pointer to the name of the EU.
*   @param[in]  euEntryPoint  The address where the EU should begin execution
*                             Portable programs should define the entrypoint
*                             with the AAEU_PROCESS macro.
*   @param[in]  euStackSize   Specifies the size (in bytes) of the stack.
*   @param[in]  euPolicy      Scheduling policy for the EU.
*   @param[in]  euPriority    The priority level for the realtime EU.
*   @param[in]  euNiceness    The nice level for the background EU.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new EU.
*   @param[in]  sizeOfeuArg   Size of the argument (in bytes) to forward to EU.
*   @param[in]  join          Defines if EU is joinable or not.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*   This function creates and starts a priorized execution unit as a real-time
*   or background process.
*   In case (sizeOfeuArg > 0):
*   Changes in #euArgPtr causes no effect to the created
*   EU after creation, because AaProEuCreateAndStart() function copy #euArgPtr.
*   In case (sizeOfeuArg == 0):
*   Modification of the memory where #euArgPtr is pointing to does have effect to the created
*   EU after creation, because AaProEuCreateAndStart() function passes the #euArgPtr
*   directly to the pthread. The user is responsible for freeing the memory to which #euArgPtr refers.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_OutOfResources if maximum number of EUs would be
*        exceeded
*
*   @par Restrictions:
*   This function is used on Linux target only.
*
*   @par Example:
*   Following example shows how to create and start execution unit
*
*   @code
*   // example 1 - with argument copy (sizeOfeuArg > 0)
*
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
*
*   // example 2 - no argument copy (sizeOfeuArg == 0)
*
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
*         0,                                    // no arg copy, pass pointer directly
*         GLO_FALSE);
*
*   // do not free param until the thread has finished!
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
*   @endcode
*
*   @par Usage:
*   Macro #AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
*   in the context of the new EU. See example.
*
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCurrent
*
******************************************************************************/
EAaProEuRetVal
AaProEuCreateAndStartWithPolicy( u32*                     euIdPtr,
                                 const char               *euNamePtr,
                                 TAaProEuEntryPoint       *euEntryPoint,
                                 u32                      euStackSize,
                                 EAaProEuSchedulingPolicy euPolicy,
                                 u32                      euPriority,
                                 i32                      euNiceness,
                                 void*                    euArgPtr,
                                 u32                      sizeOfeuArg,
                                 TBoolean                 join );


/**
*******************************************************************************
*
*   @brief      Creates and starts a priorized and joinable execution unit
*
*   @param[out] euIdPtr       Pointer to the variable where ID of the created
*                             EU stored.
*   @param[in]  euNamePtr     A pointer to the name of the EU.
*   @param[in]  euEntryPoint  The address where the EU should begin execution
*                             Portable programs should define the entrypoint
*                             with the AAEU_PROCESS macro.
*   @param[in]  euStackSize   Specifies the size (in bytes) of the stack.
*   @param[in]  euPriority    The priority level for the EU.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new EU.
*   @param[in]  sizeOfeuArg   Size of the argument (in bytes) to forward to
*                             EU.
*   @param[in]  join          Defines if EU is joinable or not.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*   This function creates and starts a priorized and joinable execution unit.
*   User have to release euArgPtr pointer after creating a Eu. Changes in
*   #euArgPtr not effect to the created Eu after creation, because
*   AaProEuCreateAndStart() function copy #euArgPtr. If join is used function
*   waits as long as EU is killed
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_OutOfResources if maximum number of EUs would be
*        exceeded
*
*   @par Restrictions:
*   This API function does not support configurability of scheduling options.
*   Rationale for this is that scheduling options can be made configurable in
*   compile time (e.g. via header files), runtime configurability is not
*   required. Also this will keep the API simpler and application SW using
*   the API will be portable (scheduling options may differ among OSs).
*
*   @par Example:
*   Following example shows how to create and start joinable execution unit
*
*   @code
*
*    #include <IfAaPro.h>
*
*    TAaProEuEntryPoint exampleEuStart;
*
*    EAaProEuRetVal ret;
*    u32 euId;
*    TBoolean join = GLO_TRUE;
*
*    ret = AaProEuCreateAndStartJoinable
*               (&euId,
*                "exampleEu",       // EU name
*                exampleEuStart     // Start function
*                2048,              // Stack size
*                EU_PRIORITY_05,    // Priority
*                GLO_NULL,
*                0,
*                join);
*
*
*    AAEU_PROCESS(exampleEuStart)
*    {
*      // code
*
*      return GLO_NULL;
*    }
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
*   @see AaProEuCurrent
*
******************************************************************************/
EAaProEuRetVal
AaProEuCreateAndStartJoinable( u32*                 euIdPtr,
                               const char          *euNamePtr,
                               TAaProEuEntryPoint  *euEntryPoint,
                               u32                  euStackSize,
                               u32                  euPriority,
                               void*                euArgPtr,
                               u32                  sizeOfEuArg,
                               TBoolean             join );

/**
*******************************************************************************
*
*   @brief      Creates and starts a priorized execution unit setting stack
*               to given OS pool. On linux this api is identical to AaProEuCreateAndStart
* 				(see restrictions)
*
*   @param[out] euIdPtr       Pointer to the variable where ID of the created
*                             EU stored.
*   @param[in]  euNamePtr     A pointer to the name of the EU.
*   @param[in]  euEntryPoint  The address where the EU should begin execution
*                             Portable programs should define the entrypoint
*                             with the AAEU_PROCESS macro.
*   @param[in]  euStackSize   Specifies the size (in bytes) of the stack.
*   @param[in]  euOsPoolId    OS poolId where stack is placed.
*   @param[in]  euPriority    The priority level for the EU.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new EU.
*   @param[in]  sizeOfeuArg   Size of the argument (in bytes) to forward to
*                             EU.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*   This function creates and starts a priorized execution unit and sets the
*   process stack to given pool. Changes in  #euArgPtr causes no effect to the
*   created Eu after creation, because AaProEuCreateAndStart() function copy
*   #euArgPtr.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - #EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_OutOfResources if maximum number of EUs would be
*        exceeded
*
*   @par Restrictions:
*   This API function does not support configurability of scheduling options.
*   Rationale for this is that scheduling options can be made configurable in
*   compile time (e.g. via header files), runtime configurability is not
*   required. Also this will keep the API simpler and application SW using
*   the API will be portable (scheduling options may differ among OSs).
* 	On linux this API function is identical to AaProEuCreateAndStart, which means that
* 	euOsPoolId parameter is ignored, and the rest of parameters are simply passed to
* 	AaProEuCreateAndStart API.
*
*   @par Example:
*   Following example shows how to create and start execution unit
*
*   @code
*
*   #include <IfAaPro.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaProEuCreateAndStartToPool
*         &euId,
*         "exampleEu",       // EU name
*         exampleEuStart     // Start function
*         2048,              // Stack size
*         0,                 // PoolId
*         EU_PRIORITY_05,    // Priority
*         (void*)&param,
*         sizeof(param));
*
*
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     u32* ret = AaMemMalloc(sizeof(u32)); // Return value must be dynamically allocated
*
*     // code
*
*     *ret = 0x1234;
*
*     return (void*)ret;
*   }
*
*   @endcode
*
*   @par Usage:
*   Macro #AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
*   in the context of the new EU. See example.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuCurrent
*
******************************************************************************/
EAaProEuRetVal
AaProEuCreateAndStartToPool( u32*                 euIdPtr,
                             const char          *euNamePtr,
                             TAaProEuEntryPoint  *euEntryPoint,
                             u32                  euStackSize,
                             u16                  euOsPoolId,
                             u32                  euPriority,
                             void*                euArgPtr,
                             u32                  sizeOfeuArg );

/**
*******************************************************************************
*
*   @brief      Returns the EU ID of the own EU.
*
*   @return     EU ID
*
*   @par Description:
*   This function returns the EU ID of the own EU. ID is unique inside system and
*   is same as system ID of EU (f.e. TID number on Linux).
*
*   @par Errors:
*   No errors are defined
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to get the EU ID of the own EU
*
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 euId = AaProEuCurrent();
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
*   @see AaProEuGetName
*
******************************************************************************/
u32 AaProEuCurrent(void);


/**
*******************************************************************************
*
*   @brief      Returns the name of the EU identified by euId.
*
*   @param[in]  euId    ID of the EU.
*   @param[out] buffer  Pointer to a buffer where the name is stored.
*   @param[in]  length  The size of the buffer.
*
*   @return     Pointer to the buffer given via #buffer parameter or GLO_NULL,
*               if requested EU does not exist or error has been occurred.
*
*   @par Description:
*   This function returns the name of the EU identified by #euId. User must provide
*   storage for the name. If storage size is not large enough, the EU name shall be
*   truncated so that it fits to given buffer including NULL endmark.
*
*   Definition #AAPRO_MAX_EU_NAME_LENGTH can be used to determine the needed buffer
*   size, which ensures that the name does not need truncation.
*
*   @par Errors:
*   If EU does not exist, #buffer is GLO_NULL or #length is 0, GLO_NULL is returned
*   instead of pointer to the buffer.
*
*   @par Restrictions:
*   None.
*
*   @par Example:
*   Following example shows how to get the name of the EU
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 euId;
*   char euName[AAPRO_MAX_EU_NAME_LENGTH];
*
*   euId = AaProEuCurrent();
*   if (AaProEuGetName(euId, euName, AAPRO_MAX_EU_NAME_LENGTH) != GLO_NULL)
*   {
*      // EU exists
*   }
*   else
*   {
*     // EU does not exist
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
*   @see AaProEuCreateAndStart
*   @see AaProEuCurrent
*
******************************************************************************/
char* AaProEuGetName(u32 euId, char* buffer, u32 length);

/**
*******************************************************************************
*
*   @brief      Returns the name of the EE identified by an euId residing in the EE.
*
*   @param[in]  euId    ID of the EU.
*   @param[out] buffer  Pointer to a buffer where the name is stored.
*   @param[in]  length  The size of the buffer.
*
*   @return     Pointer to the buffer given via #buffer parameter or GLO_NULL,
*               if requested EU does not exist or error has been occurred.
*
*   @par Description:
*   This function returns the EE name of the EU identified by #euId. User must provide
*   storage for the name. If storage size is not large enough, the EE name shall be
*   truncated so that it fits to given buffer including NULL endmark.
*
*   Definition #AAPRO_MAX_EE_NAME_LENGTH can be used to determine the needed buffer
*   size, which ensures that the name does not need truncation.
*
*   @par Errors:
*   If EU does not exist, #buffer is GLO_NULL or #length is 0, GLO_NULL is returned
*   instead of pointer to the buffer.
*
*   @par Restrictions:
*   EE names are only valid on Linux.
*
*   @par Example:
*   Following example shows how to get the name of the EE
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 euId;
*   char eeName[AAPRO_MAX_EE_NAME_LENGTH];
*
*   euId = AaProEuCurrent();
*   if (AaProEeGetName(euId, eeName, AAPRO_MAX_EE_NAME_LENGTH) != GLO_NULL)
*   {
*      // EU exists
*   }
*   else
*   {
*     // EU does not exist
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
*   @see AaProEeCurrent
*
******************************************************************************/
char* AaProEeGetName(u32 euId, char* buffer, u32 length);

/**
*******************************************************************************
*
*   @brief      Returns the priority of the EU Identified by euId.
*
*   @param[out] euId  ID of the EU
*
*   @return  Returns the priority of the EU or 0.
*
*   @par Description:
*   This function returns the priority of the EU, if the EU specified by euId
*   exists, otherwise returns a 0.
*
*   @par Errors:
*   No errors are defined
*
*   @par Restrictions:
*   In some systems, getting of priority of non-existent EU, leads to kernel
*   level error. For more details, see @ref dsVariation "API variation specification".
*
*   @par Example:
*   Following example shows how to get EU priority
*
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 euId;
*   u32 priority;
*
*   euId = AaProEuCurrent();
*   priority = AaProEuGetPri(euId);
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
*   @see AaProEuSetPri
*
******************************************************************************/
u32 AaProEuGetPri(u32 euId);


/**
*******************************************************************************
*
*   @brief      Sets the priority of the EU Identified by euId.
*
*   @param[in]  euId        ID of the EU
*   @param[in]  euPriority  The priority of the EU.
*
*   @return  EAaProEuRetVal_NoError
*   @return  EAaProEuRetVal_Error
*   @return  EAaProEuRetVal_InvalidValue
*   @return  EAaProEuRetVal_PermissionDenied
*
*   @par Description:
*   This function sets the priority of the EU Identified by euId.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - #EAaProEuRetVal_PermissionDenied in systems where an EU can set only
*        its own priority and setting of priority of another EU is tried.
*
*   @par Restrictions:
*   In some systems this call may not support setting of priority of another EU.
*   In these cases EU can set only its own priority and setting of priority of
*   another EU fails with return code #EAaProEuRetVal_PermissionDenied.
*   For more details see @ref dsVariation "API variation specification".
*
*   @par Example:
*   Following example shows how to set EU priority
*
*   @code
*   EAaProEuRetVal retVal = EAaProEuRetVal_NoError;
*   u32 priority = EU_PRIORITY_04;
*
*   retVal = AaProEuSetPri(AaProEuCurrent(), priority); // Sets priority of current EU
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
*   @see AaProEuGetPri
*
******************************************************************************/
EAaProEuRetVal
AaProEuSetPri( u32 euId, u32 euPriority );


/**
*******************************************************************************
*
*   @brief   Returns the EE ID of the own EE.
*
*   @return  Valid EE ID or AAPRO_INVALID_EE_ID
*
*   @par Description:
*   This function returns the EE ID of the current EE. ID is unique inside CE.
*   If current system does not support multiple EEs, AAPRO_INVALID_EE_ID is
*   returned instead.
*
*   @par Errors:
*   No errors are defined
*
*   @par Restrictions:
*   Some systems may not support consept of EE thus it is no sense for this
*   call to return any valid EE ID. It those cases #AAPRO_INVALID_EE_ID is returned.
*   It shall not be returned on any other situation. For more details see
*   @ref dsVariation "API variation specification".
*
*   @par Example:
*   Following example shows how to get the EE ID of the own EE
*
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 eeId;
*
*   eeId = AaProEeCurrent();
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
*   @see AaProEuCurrent
*
******************************************************************************/
u32
AaProEeCurrent( void );

/**
*******************************************************************************
*
*   @brief   Executes a command and blocks until the command terminates
*
*   @param[in]  command  Name of the command to execute
*   @param[in]  args     Arguments given to command prior to execution or GLO_NULL
*   @param[in]  flags    Flags to further controll execution of the process, e.g.
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
*   By setting the flag #AAPRO_FLAG_CMDEXEC_REPORT_EXIT you indictae that the
*   exit of the process shall be reported as error via the node status.
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
*   \ref AAPRO_TAG_RECOVERY_RESET is set to \c 1
*
*   In some systems full path to the command is needed to be defined depending
*   the command to be executed if command is not found in PATH environmental
*   variable. In some systems crash of the command is reported via retVal and
*   some systems crashing leads to whole system reset.
*   See @ref dsVariation "API variation specification".
*
*   @par Example:
*
*   @code
*
*   #include <IfAaPro.h>
*
*   int retval;
*   EAaProEuRetVal rc = AaProCmdExec("ps", "-A", 0, &retval); // Execute command 'ps -A'
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
EAaProEuRetVal
AaProCmdExec( const char* command, const char* args, u32 flags, int* retVal );

/**
*******************************************************************************
*
*   @brief       Registers an EU for monitoring.
*
*   @param[in]   interval  Specifies the ping interval.
*
*   @return Function returns success of operation.
*
*   @par Description:
*   An EU calls this function to tell Supervision service that it wishes
*   to be monitored. The EU must provide the anticipated ping interval.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     #define MAX_WAIT_TIME 5000000
*     #define TIMER_TIMEOUT   99999
*     #define MY_MSG_ID 0x...
*     struct SMyMessage { ... };
*     typedef struct SMyMessage SMyMessage;
*
*     u32 myEuId                  = AaProEuCurrent();
*     TAaSysComCpid myCpId        = AaSysComUserRegister(myCpId, myEuId);
*     TAaSysComSicad mySicAddress = AaSysComSicadGet(myCpId, AASYSCOM_NODE_LOCAL);
*     TAaSysTimerId timerId;
*     void *msgHandle             = AaSysComMsgCreate(MY_MSG_ID, sizeof(SMyMessage), mySicAddr);
*     SMyMessage *myMsg = (SMyMessage*) AaSysComMsgGetPayload(msgHandle);
*         ...
*     AaSysComMsgSetSender(msgHandle, mySicAddress);
*     AaSysTimermCreate(&timerId, TIMER_TIMEOUT, 0, msgHandle);
*
*     // Register for 1 sec. interval
*     EAaProEuRetVal sret = AaProEuSupervisionRegister(1000000);
*     if (sret != EAaProEuRetVal_NoError)
*     {
*       exit(EXIT_FAILURE);
*     }
*     while (!done)
*     {
*       void *msgHandle = AaSysComMsgReceive(MAX_WAIT_TIME);
*       SMyMessage *myMsg = (SMyMessage*) AaSysComMsgGetPayload(msgHandle);
*       if(myMsg->msgID == MY_MSG_ID)
*       {
*         AaProEuSupervisionPing();
*         ...
*         AaSysComMsgDestroy(&msgHandle);
*       }
*     }
*     AaProEuSupervisionUnregister();
*     AaSysComUserDeregister(myCpid);
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
*   @see
*
******************************************************************************/

EAaProEuRetVal AaProEuSupervisionRegister(
	const TAaMicroSecond interval);

/**
*******************************************************************************
*
*   @brief       Registers an critical EU for monitoring.
*
*   @param[in]   interval  Specifies the ping interval.
*
*   @return Function returns success of operation.
*
*   @par Description:
*   An EU calls this function to tell Supervision service that it wishes
*   to be monitored. The EU must provide the anticipated ping interval.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   For products using systemd, when critical EU will stop sending keepAlive signal, CC&S CE recovery
*   reboot will not occur if \ref AAPRO_TAG_RECOVERY_RESET is set to \c 1. In this situation only \c SIGABRT will
*   be sent to EU. Value is checked only after 2 missed keepAlive signals.
*
*   @par Example:
*   @code
*     #define MAX_WAIT_TIME 5000000
*     #define TIMER_TIMEOUT   99999
*     #define MY_MSG_ID 0x...
*     struct SMyMessage { ... };
*     typedef struct SMyMessage SMyMessage;
*
*     u32 myEuId                  = AaProEuCurrent();
*     TAaSysComCpid myCpId        = AaSysComUserRegister(myCpId, myEuId);
*     TAaSysComSicad mySicAddress = AaSysComSicadGet(myCpId, AASYSCOM_NODE_LOCAL);
*     TAaSysTimerId timerId;
*     void *msgHandle             = AaSysComMsgCreate(MY_MSG_ID, sizeof(SMyMessage), mySicAddr);
*     SMyMessage *myMsg = (SMyMessage*) AaSysComMsgGetPayload(msgHandle);
*         ...
*     AaSysComMsgSetSender(msgHandle, mySicAddress);
*     AaSysTimermCreate(&timerId, TIMER_TIMEOUT, 0, msgHandle);
*
*     // Register for 1 sec. interval
*     EAaProEuRetVal sret = AaProEuSupervisionRegisterCritical(1000000);
*     if (sret != EAaProEuRetVal_NoError)
*     {
*       exit(EXIT_FAILURE);
*     }
*     while (!done)
*     {
*       void *msgHandle = AaSysComMsgReceive(MAX_WAIT_TIME);
*       SMyMessage *myMsg = (SMyMessage*) AaSysComMsgGetPayload(msgHandle);
*       if(myMsg->msgID == MY_MSG_ID)
*       {
*         AaProEuSupervisionPing();
*         ...
*         AaSysComMsgDestroy(&msgHandle);
*       }
*     }
*     AaProEuSupervisionUnregister();
*     AaSysComUserDeregister(myCpid);
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
*   @see
*
******************************************************************************/

EAaProEuRetVal AaProEuSupervisionRegisterCritical(
	const TAaMicroSecond interval);

/**
*******************************************************************************
*
*   @brief    Unregisters an EU from monitoring.
**
*   @return Function returns success of operation.
*
*   @par Description:
*   An EU calls this function to tell Supervision service that it no longer
*   wishes to be monitored.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   see AaSupervisionRegister
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
*   AaProEuSupervisionRegister
*
******************************************************************************/

EAaProEuRetVal AaProEuSupervisionUnregister(void);

/**
*******************************************************************************
*
*   @brief    Sends a beacon (ping) to the Supervision service
*
*   @return Function returns success of operation.
*
*   @par Description:
*   An EU calls this function to send a ping signal to the Supervision service.
*   The EU must call this function again and again within the interval
*   specified in AaProEuSupervisionRegister. The Supervision allows the EU to miss
*   one beacon before sending an alarm.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   see AaProEuSupervisionRegister
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
*   AaProEuSupervisionRegister
*
******************************************************************************/

EAaProEuRetVal AaProEuSupervisionPing(void);

/**
*******************************************************************************
*
*   @brief  Returns the status of the Supervision service.
*
*   @return Function returns EAaProEuNodeStatus_Ok if all registered
*   processes are OK, EAaProEuNodeStatus_Nok otherwise.
*
*   @par Description:
*   The status of the service is defined as whether there are faulty processes
*   or not. As soon as an EU misses its beacon twice the status changes to
*   EAaProEuNodeStatus_Nok.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
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

EAaProEuNodeStatus AaProEuSupervisionStatus(void);


/**
*******************************************************************************
*
*   @brief      Sets the default scheduling policy for the EE
*
*   @param[in]  euPolicy  Default scheduling policy.
*
*
*   @return  EAaProEuRetVal_NoError
*   @return  EAaProEuRetVal_Error
*   @return  EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function sets the default scheduling policy for the EE.
*   EUs created with AaProEuCreateAndStart and AaProEuCreateAndStartJoinable
*   functions will have default scheduling policy.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*
*   @par Restrictions:
*   This function is used on Linux target only.
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
EAaProEuRetVal AaProEeSetDefaultSchedulingPolicy(EAaProEuSchedulingPolicy euPolicy);


/**
*******************************************************************************
*
*   @brief      Gets the default scheduling policy for the EE
*
*   @param[out] euPolicy  Pointer to default scheduling policy.
*
*
*   @return  EAaProEuRetVal_NoError
*   @return  EAaProEuRetVal_Error
*   @return  EAaProEuRetVal_NotSupported
*
*   @par Description:
*   This function gets the default scheduling policy for the EE.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_NotSupported if API is not supported on the system.
*
*   @par Restrictions:
*   This function is used on Linux target only.
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
EAaProEuRetVal AaProEeGetDefaultSchedulingPolicy(EAaProEuSchedulingPolicy *euPolicy);



/**
*******************************************************************************
*
*   @brief      Sets the nice level of the EU Identified by euId.
*
*   @param[in]  euId        ID of the EU
*   @param[in]  euNiceness  The nice level of the EU.
*
*   @return  EAaProEuRetVal_NoError
*   @return  EAaProEuRetVal_Error
*   @return  EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function sets the nice level of the EU Identified by euId.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*
*   @par Restrictions:
*   This function is used on Linux target only.
*
*   @par Example:
*   Following example shows how to set EU niceness
*
*   @code
*   EAaProEuRetVal retVal = EAaProEuRetVal_NoError;
*   i32 niceness = EU_PRIORITY_04;
*
*   retVal = AaProEuSetNiceness(AaProEuCurrent(), niceness); // Sets priority of current EU
*
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaProEuGetNiceness
*
******************************************************************************/
EAaProEuRetVal AaProEuSetNiceness(u32 euId, i32 euNiceness);


/**
*******************************************************************************
*
*   @brief      Gets the nice level of the EU Identified by euId.
*
*   @param[in]  euId           ID of the EU
*   @param[out] euNicenessPtr  Pointer to the nice level of the EU.
*
*   @return  EAaProEuRetVal_NoError
*   @return  EAaProEuRetVal_Error
*   @return  EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function gets the nice level of the EU Identified by euId.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*
*   @par Restrictions:
*   This function is used on Linux target only.
*
*   @par Example:
*   Following example shows how to set EU niceness
*
*   @code
*
*   #include <IfAaPro.h>
*
*   u32 euId;
*   i32 niceness;
*
*   euId = AaProEuCurrent();
*   retval = AaProEuGetNiceness(euId, &niceness);
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
*   @see AaProEuGetNiceness
*
******************************************************************************/
EAaProEuRetVal AaProEuGetNiceness(u32 euId, i32 *euNicenessPtr);


/**
*******************************************************************************
*
*   @brief      Sets the scheduling policy of the EU Identified by euId.
*
*   @param[in]  euId        ID of the EU
*   @param[in]  euPolicy    Scheduling policy for the EU.
*
*
*   @return  #EAaProEuRetVal_NoError
*   @return  #EAaProEuRetVal_Error
*   @return  #EAaProEuRetVal_InvalidValue
*
*   @par Description:
*   This function sets the scheduling policy of the EU Identified by euId.
*
*   @par Errors:
*   In case of errors, following codes are returned:
*      - #EAaProEuRetVal_Error if something failed.
*      - #EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*
*   @par Restrictions:
*   This function is used on Linux target only.
*
*   @par Usage:
*   None.
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
EAaProEuRetVal AaProEuSetSchedulingPolicy(u32 euId, EAaProEuSchedulingPolicy euPolicy);

/**
*******************************************************************************
*
*   @brief       Starts CPU load supervision on a CE.
*
*   @param[in]   level  is the CPU load level to detect CPU overload case,
*   @param[in]   interval  is the time in seconds to average over,
*   @param[in]   type  defines if normal (type-1) or total (type-1 and type-2) CPU load is monitored,
*   @param[in]   logging  parameter determines if CC&S should log diagnostics in CPU overload case
*   @param[in]   sicAddr  addresses the receiver of the indication message.
*
*   @return Function returns a measurementId which is used to discriminate concurrent measurement procedures,
*    and is used in the indication message and the deregister function.
*
*   @par Description:
*   This function starts an CPU load supervision on a CE. Overload situations are reported with message
*   AAPRO_CE_CPULOAD_OVERLOAD_IND_MSG to the EU using the sicAddr.
*   At DSP a load indication measurementType is limited to EAaProMeasurementType_Normal.
*   DSP CPU load is stored only in currentNormalCpuLoad. Background and IRQ load are ignored due to DSP
*   load measurement limitation.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*
*     TAaProMeasurementIdType id = AaProCeCpuLoadSupervisionRegister(95, 5, EAaProMeasurementType_Total, 1, sicAddr);
*     if (id == EAaProMeasurementIdType_InvalidValue)
*     {
*       // ERROR
*     }
*     ...
*     AaProCeCpuLoadSupervisionDeregister(id);
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
******************************************************************************/

TAaProMeasurementIdType
AaProCeCpuLoadSupervisionRegister(u32 level, u32 interval, EAaProMeasurementType type, u32 logging, TAaSysComSicad sicAddr);

/**
*******************************************************************************
*
*   @brief    Stops CPU load supervision.
*
*   @param[in]   measurementId  specifies the measurement procedure.
*
*   @par Description:
*   This function stops CPU load supervision.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   see AaProCeCpuLoadSupervisionRegister()
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
******************************************************************************/

void AaProCeCpuLoadSupervisionDeregister(TAaProMeasurementIdType measurementId);

/**
*******************************************************************************
*
*   @brief       Starts memory supervision on a CE.
*
*   @param[in]   level  level is the usage level of physical memory (as a percentage) to detect memory overload case,
*   @param[in]   sicAddr  addresses the receiver of the indication message.
*
*   @return Function returns a measurementId which is used to discriminate concurrent measurement procedures,
*    and is used in the indication message and the deregister function.
*
*   @par Description:
*   This function starts an memory supervision on a CE. Overload situations are reported with message
*   AAPRO_CE_MEMORY_OVERLOAD_IND_MSG to the EU using the sicAddr.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*
*     TAaProMeasurementIdType id = AaProCeMemorySupervisionRegister(90, sicAddr);
*     if (id == EAaProMeasurementIdType_InvalidValue)
*     {
*       // ERROR
*     }
*     ...
*     AaProCeMemorySupervisionDeregister();
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
******************************************************************************/

TAaProMeasurementIdType
AaProCeMemorySupervisionRegister(u32 level, TAaSysComSicad sicAddr);

/**
*******************************************************************************
*
*   @brief    Stops memory supervision.
*
*   @param[in]   measurementId  specifies the measurement procedure.
*
*   @par Description:
*   This function stops memory supervision.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   see AaProCeMemorySupervisionRegister()
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
******************************************************************************/

void AaProCeMemorySupervisionDeregister(TAaProMeasurementIdType measurementId);




#ifdef __cplusplus
}
#endif

#endif /* _IFAAPRO_H_*/
