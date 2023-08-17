/* ****************************************************************************
 * @brief  AaSysCom interface header file.
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_H
#define IF_MCU_RT_AASYSCOM_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Messages/IfAaSysCom_Msg.h"
#endif

/**
 * @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT
 * @ingroup dgAaSysCom
 *
 * @{
 */

/**
********************************************************************************
*
* @brief      Query name of a communication point
*
* @param[in]  userCpid    Specifies the identifier of the communication point.
*
* @return     The function returns a pointer to the name. If unsuccessful
*             (e.g. no such user is registered or no name is registered for the
*             user) NULL is returned.
*
* @par Description:
* The AaSysComUserQueryName() function reveals the name of the user-specified
* communication point.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComUserQueryCb, AaSysComUserQueryEuid
*
* @par Example:
*   @code
*       char *namePtr = GLO_NULL;
*       TAaSysComCpid cpid = TEST_CPID;
*       ...
*       namePtr = AaSysComUserQueryName(cpid);
*   @endcode
*
*******************************************************************************/
const char* AaSysComUserQueryName(const TAaSysComCpid userCpid);

/**
********************************************************************************
*
* @brief      Name a communication point.
*
* @param[in]  userCpid  Specifies the communication point that is given a name.
*
* @param[in]  userName  Specifies the name. If null the name is cleared.
*
* @return     The function returns the communication point identifier of the
*             user that was named or renamed. If unsuccessful, zero is
*             returned.
*
* @par Description:
* The AaSysComUserSetName() function attaches a name to a registered
* communication point.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComUserRegister
*
* @par Example:
*   @code
*       char *userNamePtr = "Tester";
*       TAaSysComCpid userCpid = OWN_CPID;
*       ...
*       TAaSysComCpid cpidName = AaSysComUserSetName(userCpid, userNamePtr);
*   @endcode
*
*******************************************************************************/
TAaSysComCpid AaSysComUserSetName(const TAaSysComCpid userCpid,
                                  const char* userName);

/**
********************************************************************************
*
* @brief      (Re)sets the QoS class attached to the hop.
*
* @param[in]       hopId         Identifier of the hop
*
* @param[in]       qosClass      QoS class for the hop.
*
* @return          None.
*
* @par Description:
* The AaSysComHopAttachQos() function (re)sets the QoS class attached to the
* hop. The function is used to overwrite the preset default QoS class
* (reliable) set for the hop.
*
* Hop Qos class is used to determine if syscom needs to use the Reliable
* transfer mode (RTM) to quarantee the reliable message delivery. It is
* implementation specific whether RTM is in use or not. This function is
* meant to fulfill legacy requirements about the RTM support.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComHopRegister
*
* @par Example:
*   @code
*       TAaSysComHopId hopId = AaSysComHopRegister(...);
*       ...
*       AaSysComHopAttachQos(hopId, EAaSysComQos_Unreliable);
*   @endcode
*
*******************************************************************************/
void AaSysComHopAttachQos(const TAaSysComHopId hopId,
                          const EAaSysComQos qosClass);

/**
********************************************************************************
*
* @brief      Redirect a message.
*
* @param[in]  message     Points to the pointer to the handle of the message.
*                         It is nulled by return.
*
* @param[in]  target      The target in which the message is redirected.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgRedirect() function preserves the source and
* destination addresses of the message and sends it. This function is intended
* only for the link usage.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID_1, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgRedirect(&msgPtr, msgTarget);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgRedirect(void **message, TAaSysComSicad target);

/**
********************************************************************************
*
* @brief      Gives maximum message payload size.
*
* @param[in]  messageTarget    Specifies the targeted recipient of the message.
*                              Should be specified if application does not know
*                              the link message will use.
*
* @param[in]  messagePool      Specifies pool where the buffer for the message
*                              is reserved from. Should be specified if
*                              AaSysComMsgCreateP function will be used for
*                              reserving and preparing resources for message.
*
* @param[in]  linkId           Identifier of the link via which the message
*                              will be sent. Should be specified if message
*                              will be sent via AaSysComMsgSendViaLink
*                              function.
*
* @return     Function returns maximum message payload size.
*
* @par Description:
* The AaSysComMsgGetMaxPayload() function returns maximum message payload size
* depending on given message target, used message memory pool and link id.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgCreate, AaSysComMsgCreateP, AaSysComMsgSendViaLink
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       TAaSysComMsgSize maxPayloadSize;
*       ...
*       maxPayloadSize = AaSysComMsgGetMaxPayload(msgTarget,
*                                                 UNSPECIFIED_MEMORY_POOL,
*                                                 AASYSCOM_LINK_INVALID);
*       msgPtr = AaSysComMsgCreate(msgId, maxPayloadSize, msgTarget);
*   @endcode
*
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       i32 messageMemPool = 5;
*       TAaSysComLinkId linkId = AASYSCOM_LINK_SRIO;
*       TAaSysComMsgSize maxPayloadSize;
*       ...
*       maxPayloadSize = AaSysComMsgGetMaxPayload(msgTarget,
*                                                 messageMemPool,
*                                                 linkId);
*   @endcode
*
*******************************************************************************/
TAaSysComMsgSize AaSysComMsgGetMaxPayload(const TAaSysComSicad messageTarget,
                                          const i32 messagePool,
                                          const TAaSysComLinkId linkId);

/**
********************************************************************************
*
* @brief      Resets the message identifier group of the message.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @param[in]       messageIdGroup Message identifier group of the message.
*
* @return          None.
*
* @par Description:
* The AaSysComMsgSetIdGroup() function resets the message identifier group of
* the message. The function is used to 'move the message out from the normal
* message identifier space'.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetIdGroup
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetIdGroup(msgPtr, EAaSysComMsgIdGroup_0);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetIdGroup(const void *message,
                           const EAaSysComMsgIdGroup messageIdGroup);


/**
********************************************************************************
*
* @brief      Presents the message identifier group of the message.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          The message identifier group of the message.
*
* @par Description:
* The AaSysComMsgGetIdGroup() function presents the message identifier group of
* the message. The function is used to check if 'the message has been moved out
* from the normal message identifier space'.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetIdGroup
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       EAaSysComMsgIdGroup msgIdGroup;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgIdGroup = AaSysComMsgGetIdGroup(msgPtr);
*   @endcode
*
*******************************************************************************/
EAaSysComMsgIdGroup AaSysComMsgGetIdGroup(const void *message);

/**
********************************************************************************
*
* THIS FUNCTION IS DEPRECATED, DO NOT USE. Instead the QoS can be assigned
* per hop instead of per link.
*
*******************************************************************************/
void AaSysComLinkAttachQos(const TAaSysComLinkId linkId,
                           const EAaSysComLinkQos qosClass);

/**
********************************************************************************
*
* @brief      Gets hop identifier for specified destination and link.
*
* @param[in]  destinationAddress    Specifies the destination address for which
*                                   the hop should be found.
*
* @param[in]  linkId                Specifies the link associated with the hop.
*
* @param[out] hopId                 Found hop identifier.
*
* @return     The function returns outcome of operation.
*
* @par Description:
* The AaSysComHopGetId() function gets hop identifier for specified destination
* and link.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*       TAaSysComHopId hopId = 0;
*       TAaSysComLinkId linkId = TEST_LINK_ID;
*       TAaSysComSicad destination = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       EAaSysComReturnCode rc;
*       ...
*       rc = AaSysComHopGetId(destination, TEST_LINK_ID, &hopId);
*       if(status == EAaSysComReturnCode_Ok)
*       {
*           // hop identifier was found
*       }
*   @endcode
*
*******************************************************************************/
EAaSysComReturnCode AaSysComHopGetId(const TAaSysComSicad destinationAddress,
                                     const TAaSysComLinkId linkId,
                                     TAaSysComHopId * hopId);

/**
********************************************************************************
*
* @brief      Get logical node id of the requesting user.
*
* @return     The function returns the logical SIC node identifier (NID), if successful.
*             Otherwise and in case the logical node identifier is not set yet, it
*             returns the own node-id, or- if that also doesn't exist - AASYSCOM_NODE_INVALID.
*
* @par Description:
* The AaSysComGetLogicalNid() function gets the logical node id of the requesting user.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*       TAaSysComNid logicalNid = 0;
*       ...
*       logicalNid = AaSysComGetLogicalNid();
*   @endcode
*
*******************************************************************************/
TAaSysComNid AaSysComGetLogicalNid(void);


/**
********************************************************************************
*
* @brief      Gives the length of the message queue for specified EU.
*
* @param[in]  euId    Specifies the EU ID.
*
* @return     The function returns the number of messages in specified EU's
*             message queue. In case of error -1 is returned.
*
* @par Description:
* The AaSysComGetQueueLength() returns number of messages in specified EU's
* message queue.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* This function is supported in Linux only.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*       i32 queueLength;
*       ...
*       queueLength = AaSysComGetQueueLength(AaProEuCurrent());
*       if(queueLength == -1)
*       {
*           // failed to obtain queue length
*       }
*   @endcode
*
*******************************************************************************/
i32 AaSysComGetQueueLength(const u32 euId);

/**
********************************************************************************
*
* @brief        Receive any message with queue info.
*
* @param[in]    maxTimeToWait Specifies the maximum time (in microseconds) a
*                             message is waited for. AASYSCOM_INFINITE_WAITTIME
*                             denotes infinite wait time and
*                             AASYSCOM_NO_WAITTIME denotes zero waitime. See
*                             also "USAGE" section.
*
* @param[out]   queueingTime  Points to an u32 containing the time (in
*                             microseconds) message was kept in the EU's message
*                             queue.
*
* @param[out]   queueLength   Points to an u32 containing the number of
*                             messages in EU's message queue. In case of error,
*                             -1 is returned.
*
* @param[out]   messagePoolUsage    Points to an u32 containing the IPC message
*                                   pool usage (in percent).
*
* @return     The function returns a pointer to the handle of the received
*             message, if there is a message to be received, otherwise GLO_NULL
*             is returned. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgReceiveWithQueueInfo() function points the handle of the
* received message and passes on, as arguments of the function, message queue
* info. Ownership of the message is transferred to the user.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* If no message was received, queueingTime may contain invalid value and should
* not be used.
*
* @par Usage:
* It is not recommended to use this function if user is not interested in queue
* info. Potential users are advised to consider using standard receiving
* function AaSysComMsgReceive instead due to potential implementation specific
* performance issues.
* The actual wait time is implementation specific and is affected by wait time
* rounding and tick waiting time variation. If the requested wait time is
* shorter than one system tick, the actual wait time should equal to one system
* tick. Otherwise the wait time is rounded down to the system tick resolution.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       u32 queueingTime = 0;
*       u32 queueLength = 0;
*       u32 messagePoolUsage = 0;
*       ...
*       msgPtr = AaSysComMsgReceiveWithQueueInfo(1000,
*                                                &queueingTime,
*                                                &queueLength,
*                                                &messagePoolUsage);
*       if(msgPtr != GLO_NULL)
*       {
*           // message was received and queue info is available
*       }
*       else
*       {
*           // no message received, queueingTime should not be used
*       }
*   @endcode
*
*******************************************************************************/
void* AaSysComMsgReceiveWithQueueInfo(const u32 maxTimeToWait,
                                      u32* queueingTime,
                                      u32* queueLength,
                                      u32* messagePoolUsage);

/**
********************************************************************************
*
* @brief      Receive a message of specific type with queue info.
*
* @param[in]    maxTimeToWait Specifies the maximum time (in microseconds) a
*                             message is waited for.
*                             AASYSCOM_INFINITE_WAITTIME denotes infinite wait
*                             time and AASYSCOM_NO_WAITTIME denotes zero wait
*                             ime. See also "USAGE" section.
*
* @param[in]    messageIdFilter Points to an array of accepted/rejected message
*                               identifiers (SIC message type numbers). First
*                               item in array must state the number of following
*                               identifiers. Positive sign of first item
*                               indicates that messages are accepted while
*                               negative sign indicates that messages are
*                               rejected. See example.
*
* @param[out]   queueingTime Points to an u32 containing the time (in
*                            microseconds) message was kept in the EU's message
*                            queue.
*
* @param[out]   queueLength Points to an u32 containing the number of messages
*                           in EU's message queue. In case of error, -1 is
*                           returned.
*
* @param[out]   messagePoolUsage    Points to an u32 containing the IPC message
*                                   pool usage (in percent).
*
* @return     The function returns a pointer to the handle of the received
*             message, if there is a message to be received, otherwise GLO_NULL
*             is returned. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgReceiveSelectiveWithQueueInfo() function returns the handle of
* the received message, message identifier (SIC message type number) of which
* conforms to the user-specified rules, and queue info. Ownership of the message
* is transferred to the user.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* If no message was received, queueingTime may contain invalid value and should
* not be used.
*
* @par Usage:
* It is not recommended to use this function if user is not interested in queue
* info. Potential users are advised to consider using standard receiving
* function AaSysComMsgReceive instead due to potential implementation specific
* performance issues.
* The actual wait time is implementation specific and is affected by wait time
* rounding and tick waiting time variation. If the requested wait time is
* shorter than one system tick, the actual wait time should equal to one system
* tick. Otherwise the wait time is rounded down to the system tick resolution.
* Receive returns to the caller when a message matching any of the specified
* message types is found or max wait time has expired. The first position in
* messageIdFilter contains the number of entries in the list that follows.
* Positive sign of first item indicates that messages are accepted while
* negative sign indicates that messages are rejected. If the number of entries
* is zero, all messages are accepted.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgIdFilter[] = {2, TEST_MSG1, TEST_MSG2};
*       u32 queueingTime = 0;
*       u32 queueLength = 0;
*       u32 messagePoolUsage = 0;
*       ...
*       msgPtr = AaSysComMsgReceiveSelectiveWithQueueInfo(1000,
*                                                         msgIdFilter,
*                                                         &queueingTime,
*                                                         &queueLength,
*                                                         &messagePoolUsage);
*       if(msgPtr != GLO_NULL)
*       {
*           // message was received and queue info is available
*       }
*       else
*       {
*           // no message received, queueingTime should not be used
*       }
*   @endcode
*
*******************************************************************************/
void* AaSysComMsgReceiveSelectiveWithQueueInfo(const u32 maxTimeToWait,
                                               const TAaSysComMsgId *messageIdFilter,
                                               u32* queueingTime,
                                               u32* queueLength,
                                               u32* messagePoolUsage);

/**
********************************************************************************
*
* @brief    Get IPC message pool usage.
*
* @return   The function returns message pool usage (in percent).
*
* @par Description:
* The AaSysComGetIpcMessagePoolUsage() function returns message pool usage.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* None.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*       u32 messagePoolUsage = 0;
*
*       messagePoolUsage = AaSysComGetIpcMessagePoolUsage();
*   @endcode
*
*******************************************************************************/
u32 AaSysComGetIpcMessagePoolUsage(void);


/**
********************************************************************************
*
*   @brief    Attach a SysCom message queue to the calling thread.
*
*   @return   GLO_TRUE if a message queue has been attached.
*             GLO_FALSE otherwise.
*
*   @par Description:
*   The AaSysComMsgQueueCreate() function adds a message queue to the calling thread.
*   If there is already a message queue assigned to this thread, it does nothing.
*   When a new message queue has been added successfully, this function subscribes to an 
*   AaPro ExitHandler to get rid of the message queue on thread exit.
*   Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
*   (layering of AaSysCom and AaPro).
*
*   @par Errors:
*   In case of an error this function returns GLO_FALSE.
*
*   @par Restrictions:
*   None.
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None.
*
*   @par Example:
*   Following example shows how to add a message queue to the calling thread.
*   Note: The calling thread was created via e.g. AaProEuCreateAndStart
*
*       @code
*       AAEU_PROCESS(exampleEuStart)
*       {
*           // prior code
*
*           if (GLO_FALSE == AaSysComMsgQueueCreate())
*           {
*               // print error log message
*               return;
*           }
*
*           // normal thread handling follows
*       }
*       @endcode
*
*******************************************************************************/
TBoolean AaSysComMsgQueueCreate(void);

/**
********************************************************************************
*
*   @brief    Detach a SysCom message queue from the calling thread.
*
*   @return   None
*
*   @par Description:
*   The AaSysComMsgQueueDelete() function detaches a message queue from the calling thread
*   and deletes it.
*   If there is no message queue assigned to this thread, it does nothing.
*   When a message queue has been detached successfully, this function unsubscribes to the 
*   AaPro ExitHandler.
*   Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
*   (layering of AaSysCom and AaPro).
*
*   @par Errors:
*   None.
*
*   @par Restrictions:
*   None.
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None.
*
*   @par Example:
*   Following example shows how to delete a message queue currently attached to the calling thread.
*   Note: The calling thread was created via e.g. AaProEuCreateAndStart
*
*       @code
*       AAEU_PROCESS(exampleEuStart)
*       {
*           // prior code
*
*           AaSysComMsgQueueDelete();
*
*           // normal thread handling follows, if any
*       }
*       @endcode
*
*******************************************************************************/
void AaSysComMsgQueueDelete(void);



/**
********************************************************************************
*
* @brief    Register for EE shutdown notification message.
*
* @return   The function returns nothing.
*
* @par Description:
* The AaSysComEuEnableCleanup() registers EU to receive EE shutdown notification
* message. This enables EU to perform a cleanup in case of EE shutdown.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* None.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None.
*
* @par Example:
*   @code
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*     TAaSysComCpid cpid = AASYSCOM_CP_INVALID;
*     void *msgPtr = GLO_NULL;
*     TAaSysComMsgId msgId = 0;
*     TBoolean running = GLO_TRUE;
*
*     cpid = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
*     AaSysComEuEnableCleanup();
*     ...
*     while(running)  // EU message loop
*     {
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       if (msgPtr != 0)
*       {
*         msgId = AaSysComMsgGetId(msgPtr);
*         switch (msgId)
*         {
*           case AASYSCOM_EE_SHUTDOWN_NOTIF_MSG:
*             // shutdown in progress -> exit message loop
*             running = GLO_FALSE;
*             break;
*           case ...
*         }
*         AaSysComMsgDestroy(&msgPtr);
*       }
*     }
*
*     AaSysComUserDeregister(cpid);
*     return GLO_NULL;
*   }
*   @endcode
*
*******************************************************************************/
void AaSysComEuEnableCleanup(void);

/** @} end: @addtogroup dgAaSysComApiMcu AaSysCom MCU API */


#ifdef __cplusplus
}
#endif


#endif /* IF_MCU_RT_AASYSCOM_H */
