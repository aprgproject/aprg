/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 System Dispatcher API header file
* @module                AaSysDispatcher
* @owner                 Matija Buskovic
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAASYSDISPATCHER_H
#define _IFAASYSDISPATCHER_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@defgroup dgAaSysDispatcher System Dispatching Service
*@ingroup dgBasicSystemSw
*
*/

/**
*@defgroup dgAaSysDispatcherApi API
*@ingroup dgAaSysDispatcher
*
* Application Programming Interface.
* 
* API specification (current): 
*
*@{*/


/*----------------------- INCLUDED FILES --------------------------------------*/

#include <IfAaSysCom.h>
#include <IfAaPro.h>

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/** @brief AaSysDispatcher public return codes */
typedef enum EAaSysDispatcherStatus
{
    EAaSysDispatcherStatus_Ok = 0,
    EAaSysDispatcherStatus_Fail
}EAaSysDispatcherStatus;

/** @brief Function for handling SIC messages */
typedef void * (*TSicDispatcherFunc) (void **msg);

/** @brief Function for handling SIC messages with additional parameter */
typedef void * (*TSicDispatcherWithParamFunc) (void **msg, void *userParam);

/** @brief Function which is executed when EU is started */
typedef void (*TSysDispatcherConstructor) (void * param);

/** @brief Function which is executed when EU is destroyed */
typedef void (*TSysDispatcherDestructor) (void * param);

/** @brief Sic handler: function and message id pair*/
typedef struct SSysDispatcherSicHandler
{
    TAaSysComMsgId      msgId;
    TSicDispatcherFunc  function;
}SSysDispatcherSicHandler;

/** @brief Sic handler: function and message id pair with additional parameter */
typedef struct SSysDispatcherWithParamSicHandler
{
    TAaSysComMsgId msgId;
    TSicDispatcherWithParamFunc function;
    void *userParam;
} SSysDispatcherWithParamSicHandler;


/* SIC Dispathcer part */

/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**@name AaSysDispatcher public API
 * @{
 */
 

/**
 * @defgroup dgAaSysDispatcherApiCommon AaSysDispatcher COMMON API
 * @ingroup  dgAaSysDispatcher
 */

/* @{ */

/**
*******************************************************************************
*
* @brief      Creates and starts a priorized SIC dispatcher execution unit
*
* @param[in]  numOfCpId       Number of CPIDs to bind at startup time
* @param[in]  cpId            Pointer to CPID list
* @param[in]  euNamePtr       A pointer to the name of the EU.
* @param[in]  stackSize       Specifies the size (in bytes) of the stack.
* @param[in]  priority        The priority level for the EU.
* @param[in]  userConstructor User function which is called at dispatcher instance
*                               start
* @param[in]  userConstructorParam Parameters for above function
* @param[in]  userExceptionHandler User exception handler
*
* @return
*   Returns pointer to SIC dispatcher instance on success and NULL in the case of failure.
*
* @par Description:
*   This function creates and starts a priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to create and start execution unit
*
* @code
*
*   void * sysDispatcherInstance;
*
*   const TAaSysComCpid cpId[] = {TESTCPID1, TESTCPID2};
*
*   sysDispatcherInstance = AaSysDispatcherSicEuCreate(2,
*                                                      cpId,
*                                                      "TestInstance",
*                                                      1024,
*                                                      EU_PRIORITY_14,
*                                                      ConstructorFunction,
*                                                      NULL,
*                                                      ExceptionHandlerFunction);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicEuDestroy
*
******************************************************************************/
void * AaSysDispatcherSicEuCreate(u32 const                           numOfCpId,
                                  TAaSysComCpid const                *cpId,
                                  const char                         *euNamePtr,
                                  u32 const                           stackSize,
                                  u32 const                           priority,
                                  TSysDispatcherConstructor           userConstructor,
                                  void                               *userConstructorParam,
                                  TSicDispatcherFunc                  userExceptionHandler);

/**
*******************************************************************************
*
* @brief      Creates and starts a prioritized SIC dispatcher execution unit
*
* @param[in]  numOfCpId       Number of CPIDs to bind at startup time
* @param[in]  cpId            Pointer to CPID list
* @param[in]  euNamePtr       A pointer to the name of the EU.
* @param[in]  stackSize       Specifies the size (in bytes) of the stack.
* @param[in]  priority        The priority level for the EU.
* @param[in]  userConstructor User function which is called at dispatcher instance
*                               start
* @param[in]  userConstructorParam Parameters for above function
* @param[in]  userExceptionHandler User exception handler
* @param[in]  userExceptionHandlerParam User exception handler parameter
*
* @return
*   Returns pointer to SIC dispatcher instance on success and NULL in the case of failure.
*
* @par Description:
*   This function creates and starts a prioritized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to create and start execution unit
*
* @code
*
*   void * sysDispatcherInstance;
*
*   const TAaSysComCpid cpId[] = {TESTCPID1, TESTCPID2};
*
*   sysDispatcherInstance = AaSysDispatcherWithParamSicEuCreate(2,
*                                                               cpId,
*                                                               "TestInstance",
*                                                               1024,
*                                                               EU_PRIORITY_14,
*                                                               ConstructorFunction,
*                                                               NULL,
*                                                               ExceptionHandlerFunction.
                                                                param);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicEuDestroy
*
******************************************************************************/
void * AaSysDispatcherWithParamSicEuCreate(u32 const numOfCpId,
                                           TAaSysComCpid const *cpId,
                                           const char *euNamePtr,
                                           u32 const stackSize,
                                           u32 const priority,
                                           TSysDispatcherConstructor userConstructor,
                                           void *userConstructorParam,
                                           TSicDispatcherWithParamFunc userExceptionHandler,
                                           void *userExceptionHandlerParam);


/**
*******************************************************************************
*
* @brief      Creates and starts a priorized SIC dispatcher execution unit and
*               locates stack to wanted OS pool.
*
* @param[in]  numOfCpId       Number of CPIDs to bind at startup time
* @param[in]  cpId            Pointer to CPID list
* @param[in]  euNamePtr       A pointer to the name of the EU.
* @param[in]  stackSize       Specifies the size (in bytes) of the stack.
* @param[in]  euOsPoolId      OS Pool where stack of EU is located.
* @param[in]  priority        The priority level for the EU.
* @param[in]  userConstructor User function which is called at dispatcher instance
*                               start
* @param[in]  userConstructorParam Parameters for above function
* @param[in]  userExceptionHandler User exception handler
*
* @return
*   Returns pointer to SIC dispatcher instance on success and NULL in the case of failure.
*
* @par Description:
*   This function creates and starts a priorized SIC dispatcher execution unit
*   and locates the EU stack to wanted OS pool.
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to create and start execution unit
*
* @code
*
*   void * sysDispatcherInstance;
*
*   const TAaSysComCpid cpId[] = {TESTCPID1, TESTCPID2};
*
*   sysDispatcherInstance = AaSysDispatcherSicEuCreateToPool(2,
*                                                            cpId,
*                                                            "TestInstance",
*                                                            1024,
*                                                            3,
*                                                            EU_PRIORITY_14,
*                                                            ConstructorFunction,
*                                                            NULL,
*                                                            ExceptionHandlerFunction);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicEuDestroy
*
******************************************************************************/
void * AaSysDispatcherSicEuCreateToPool(u32 const                     numOfCpId,
                                        TAaSysComCpid const           *cpId,
                                        const char                    *euNamePtr,
                                        u32 const                     stackSize,
                                        u16                           euOsPoolId,
                                        u32 const                     priority,
                                        TSysDispatcherConstructor     userConstructor,
                                        void                         *userConstructorParam,
                                        TSicDispatcherFunc            userExceptionHandler);

/**
*******************************************************************************
*
* @brief      Destroys a priorized SIC dispatcher execution unit
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  userDestructor        User function which is called before
*                                     dispatcher instance is destroyed
* @param[in]  userDestructorParam   Parameters for above function
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function destroyes a priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to destroy SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherSicEuDestroy(sysDispatcherInstance,
*                                        DestructorFunction,
*                                        NULL);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicEuCreate
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherSicEuDestroy (void const ** const       sysDispatcherInstance,
                                                    TSysDispatcherDestructor  userDestructor,
                                                    void                     *userDestructorParam);

/**
*******************************************************************************
*
* @brief      Destroys a priorized SIC dispatcher execution unit with additional
*               parameter, as part of CN5611
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  userDestructor        User function which is called before
*                                     dispatcher instance is destroyed
* @param[in]  userDestructorParam   Parameters for above function
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function destroyes a priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to destroy SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherWithParamSicEuDestroy(sysDispatcherInstance,
*                                                 DestructorFunction,
*                                                 NULL);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicEuCreate
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherWithParamSicEuDestroy(void const ** const       sysDispatcherInstance,
                                                            TSysDispatcherDestructor  userDestructor,
                                                            void                     *userDestructorParam);

/**
*******************************************************************************
*
* @brief      Bind CPID to existing SIC dispatcher execution unit
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  cpId                  CPID
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function binds CPID to existing priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to unbind CPID to SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherSicEuCpidBind(sysDispatcherInstance,
*                                         TESTCPID3);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaProEuCurrent
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherSicEuCpidBind(void const * const  sysDispatcherInstance,
                                                   TAaSysComCpid const cpId);

/**
*******************************************************************************
*
* @brief      Bind CPID to existing SIC dispatcher execution unit,
*               introduced with CN5611 - for additional parameter
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance with
*                                     additional parameter
* @param[in]  cpId                  CPID
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function binds CPID to existing priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to unbind CPID to SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherWithParamSicEuCpidBind(sysDispatcherInstance,
*                                                  TESTCPID3);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaProEuCurrent
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherWithParamSicEuCpidBind(void const * const  sysDispatcherInstance,
                                                             TAaSysComCpid const cpId);

/**
*******************************************************************************
*
* @brief      Unbind CPID to existing SIC dispatcher execution unit
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  cpId                  CPID
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function unbinds CPID from existing priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to unbind CPID from SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherSicEuCpidUnbind(sysDispatcherInstance,
*                                           TESTCPID3);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaProEuCurrent
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherSicEuCpidUnbind(void const * const  sysDispatcherInstance,
                                                      TAaSysComCpid const cpId);

/**
*******************************************************************************
*
* @brief      Unbind CPID to existing SIC dispatcher execution unit for CN5611
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
*                                     with additional parameter
* @param[in]  cpId                  CPID
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function unbinds CPID from existing priorized SIC dispatcher execution unit
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to unbind CPID from SIC dispatcher instance
*
* @code
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherWithParamSicEuCpidUnbind(sysDispatcherInstance,
*                                                    TESTCPID3);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaProEuCurrent
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherWithParamSicEuCpidUnbind(void const * const  sysDispatcherInstance,
                                                               TAaSysComCpid const cpId);

/**
*******************************************************************************
*
* @brief      Bind SIC message handlers to existing SIC dispatcher execution unit
*               and CPID
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  cpId                  CPID to which handlers are going to be bound
* @param[in]  numOfHandlersToBind   Number of message handlers to bind
* @param[in]  handlePtr             Pointer to message handlers
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function binds message handlers (message handling functions and IDs)
*   to existing priorized SIC dispatcher execution unit and specified CPID
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to bind SIC message handlers to existing
*   SIC dispatcher and CPID
*
* @code
*
*   static const SSysDispatcherSicHandler msgHandles[]=
*   {
*       {SET_RAD_PARAMS_REQ_MSG,                 SetRadParamsReqHandler},
*       {GET_RAD_PARAMS_REQ_MSG,                 GetRadParamsReqHandler}
*   };
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherSicBind(sysDispatcherInstance,
*                                   TESTCPID3,
*                                   sizeof(msgHandles)/sizeof(SSysDispatcherSicHandler),
*                                   msgHandles);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicUnbind
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherSicBind(void     const * const                 sysDispatcherInstance,
                                              TAaSysComCpid const                    cpId,
                                              u32 const                              numOfHandlersToBind,
                                              SSysDispatcherSicHandler const * const handlePtr);

/**
*******************************************************************************
*
* @brief      Bind SIC message handlers to existing SIC dispatcher execution unit
*               and CPID with additional parameter
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  cpId                  CPID to which handlers are going to be bound
* @param[in]  numOfHandlersToBind   Number of message handlers to bind
* @param[in]  handlePtr             Pointer to message handlers
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function binds message handlers (message handling functions and IDs)
*   to existing priorized SIC dispatcher execution unit and specified CPID
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to bind SIC message handlers to existing
*   SIC dispatcher and CPID
*
* @code
*
*   static const SSysDispatcherWithParamSicHandler msgHandlesWithParam[]=
*   {
*       {SET_RAD_PARAMS_REQ_MSG, SetRadParamsReqHandler, userParam1},
*       {GET_RAD_PARAMS_REQ_MSG, GetRadParamsReqHandler, userParam2}
*   };
*
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherWithParamSicBind(sysDispatcherInstance,
*                                            TESTCPID3,
*                                            sizeof(msgHandlesWithParam)/sizeof(SSysDispatcherWithParamSicHandler),
*                                            msgHandlesWithParam);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherWithParamSicUnbind
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherWithParamSicBind(void     const * const                 sysDispatcherInstance,
                                                       TAaSysComCpid const                    cpId,
                                                       u32 const                              numOfHandlersToBind,
                                                       SSysDispatcherWithParamSicHandler const * const handlePtr);

/**
*******************************************************************************
*
* @brief      Unbind SIC message handlers from existing SIC dispatcher execution unit
*
* @param[in]  sysDispatcherInstance Pointer to SIC dispatcher instance
* @param[in]  cpId                  CPID to which handlers are going to be bound
* @param[in]  numOfHandlersToUnbind Number of message handlers to unbind
* @param[in]  msgId                 Pointer to message ID list
*
* @return
*      EAaSysDispatcherStatus
*
* @par Description:
*   This function unbinds message handlers from existing priorized SIC
*    dispatcher execution unit and CPID
*
* @par Errors:
*   No errors are defined
*
* @par Restrictions:
*      - None
*
* @par Example:
*   Following example shows how to unbind message handlers from SIC dispatcher
*   instance and CPID
*
* @code
*
*   static const TAaSysComMsgId msgList[]=
*   {
*       SET_RAD_PARAMS_REQ_MSG,
*       GET_RAD_PARAMS_REQ_MSG
*   };
*
*   EAaSysDispatcherStatus status;
*
*   status = AaSysDispatcherSicUnbind(sysDispatcherInstance,
*                                     TESTCPID3,
*                                     sizeof(msgList)/sizeof(TAaSysComMsgId),
*                                     msgHandles);
*
* @endcode
*
* @par Usage:
*   None
*
* @par Rationale:
*   None
*
* @par Future directions:
*   None
*
* @see AaSysDispatcherSicBind
*
******************************************************************************/
EAaSysDispatcherStatus AaSysDispatcherSicUnbind(void const * const           sysDispatcherInstance,
                                                TAaSysComCpid const          cpId,
                                                u32 const                    numOfHandlersToUnbind,
                                                TAaSysComMsgId const * const msgId);

/* @} */


#ifdef __cplusplus
}
#endif

/*@}*/


/*@}*/


#endif

