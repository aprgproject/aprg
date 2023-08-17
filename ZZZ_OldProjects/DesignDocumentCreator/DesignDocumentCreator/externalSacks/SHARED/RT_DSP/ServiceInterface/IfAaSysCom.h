/**
*******************************************************************************
* @file
*
* @brief                 AaSysCom interface header file.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSCOM_H
#define _RT_DSP_IFAASYSCOM_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysCom AaSysCom API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysCom AaSysCom API for RT and OSECK DSP nodes
* @{
*/

/**
********************************************************************************
*
* @brief      Extract a SysCom message from an event.
*
* @param[in]  eventPtr  Pointer to the event.
*
* @return     The function returns a pointer to the message.
*
* @par Description:
* The AaSysComMsgExtractFromEvent() function extracts a message from the event
*
* @deprecated Use em_get_event_buffer() instead For CC&S-RT, use
*             em_event_pointer() instead
*
*******************************************************************************/
#if !defined(CCS_RT_EM_API)
#define AaSysComMsgExtractFromEvent(eventPtr)  em_get_event_buffer(eventPtr)
#else
#define AaSysComMsgExtractFromEvent(eventPtr)  em_event_pointer (eventPtr)
#endif /*!defined(CCS_RT_EM_API)*/

/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a message from a
*               user-specified AaMem pool.
*
* @param[in]    messageId           Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    messageTarget       Specifies the targeted recipient of the
*                                   message (SIC address of the target).
*
* @param[in]    messagePool         Specifies AaMem pool where the buffer of
*                                   the message is reserved from.
*
* @return       The function returns a pointer to the handle of the new
*               message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateP() function reserves and prepares resources, especially
* a buffer from the user-specified AaMem pool, for the message.
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
* AaSysComMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       i32 myAaMemPoolId = 5;
*       ...
*       msgPtr = AaSysComMsgCreateP(msgId,
*           msgPayloadSize,
*           msgTarget,
*           myAaMemPoolId);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateP(const TAaSysComMsgId messageId,
                         const TAaSysComMsgSize messagePayloadSize,
                         const TAaSysComSicad messageTarget,
                         const i32 messagePool);

/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a message from a
*               user-specified AaMem pool.
*
* @param[in]    messageId           Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    messageTarget       Specifies the targeted recipient of the
*                                   message (SIC address of the target).
*
* @param[in]    messagePool         Specifies AaMem pool where the buffer of
*                                   the message is reserved from.
*
* @param[in]    functionNamePtr     Specifies function name where this function
*                                   was called.
*
* @param[in]    lineNumber          Specifies the line number of the source file
*                                   where this function was called.
*
* @return       The function returns always a valid pointer to the handle of
*               the new message.
*
* @par Description:
* The AaSysComMsgCreateSafePInternal() function reserves and prepares resources,
* especially a buffer from the user-specified AaMem safe pool, for the message.
*
* @par Errors:
* If allocation from safe pool fails then fatal exception handler is called.
*
* @par Restrictions:
* Used only from AASYSCOM_MSG_CREATE_SAFE_P -macro!
*
* @par Usage:
* Use of this function straight is not recommended.
* Used only from AASYSCOM_MSG_CREATE_SAFE_P -macro!
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AASYSCOM_MSG_CREATE_SAFE_P
*
*******************************************************************************/
void *AaSysComMsgCreateSafePInternal(const TAaSysComMsgId   messageId,
                                     const TAaSysComMsgSize messagePayloadSize,
                                     const TAaSysComSicad   messageTarget,
                                     const i32              messagePool,
                                     const char            *functionNamePtr,
                                     const u32              lineNumber);

/**
********************************************************************************
*
* @brief        AASYSCOM_MSG_CREATE_SAFE_P -macro reserves and prepares
*               resources safely for a message from a user-specified
*               AaMem safe pool.
*
* @param[out]   messagePtrPtr       Pointer to message pointer where the address
*                                   of the allocated message is stored.
*                                   Never GLO_NULL is stored.
*
* @param[in]    messageId           Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    messageTarget       Specifies the targeted recipient of the
*                                   message (SIC address of the target).
*
* @param[in]    messagePool         Specifies AaMem pool where the buffer of
*                                   the message is reserved from.
*
* @par Description:
* The AASYSCOM_MSG_CREATE_SAFE_P macro reserves and prepares resources,
* especially a buffer from the user-specified AaMem safe pool, for the message.
* Returns always a pointer to message. If allocation fails then this macro
* calls fatal error handler.
*
* @par Errors:
* If allocation from AaMem safe pool fails then Fatal error is raised except
* if safe allocator isn't defined.
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
* AaSysComMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       i32 myAaMemPoolId = 5;
*       ...
*       AASYSCOM_MSG_CREATE_SAFE_P(&msgPtr,
*           msgId,
*           msgPayloadSize,
*           msgTarget,
*           myAaMemPoolId);
*
*       //No need to check pointer here.
*   @endcode
*
*******************************************************************************/
#define AASYSCOM_MSG_CREATE_SAFE_P(messagePtrPtr, \
                                   messageId, \
                                   messagePayloadSize, \
                                   messageTarget, \
                                   messagePool) \
{\
    *messagePtrPtr = AaSysComMsgCreateSafePInternal(messageId, \
                                                messagePayloadSize, \
                                                messageTarget, \
                                                messagePool, \
                                                __FUNCTION__, \
                                                __LINE__); \
}\

/**
********************************************************************************
*
* @brief      Get the handle of message.
*
* @param[in]    messagePayload  Points to an object containing the message
*                               application part (user payload) of a message.
*
* @return     The function returns a pointer to the handle of the message. In
*             case of errors (e.g. no such message) NULL is returned.
*
* @par Description:
* The AaSysComMsgReveal() function points the handle of the message the
* user-specified payload belongs to.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* Use if this function is not recommended. It may be used e.g. to simplify
* porting of legacy software but in new development its use should be avoided.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetPayload, AaSysComMsgDestroy, AaSysComMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *payloadPtr = GLO_NULL;
*       void *handlePtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payloadPtr = AaSysComMsgGetPayload(msgPtr);
*       handlePtr = AaSysComMsgReveal(payloadPtr);
*       if(msgPtr == handlePtr)
*       {
*           //Operation successful
*       }
*
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgReveal(const void *messagePayload);

/**
********************************************************************************
*
* @brief      Set the default message transfer mode of messages created by the
*             calling EE.
*
* @param[in]  requestedTransferMode Specifies the default transfer mode of
*                                   messages created by this EE.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComEeSetMtmDefault() function provides the ability to set the default
* transfer mode of messages created by this EE. Transfer mode for individual
* messages can still be modified via AaSysComMsgSetMtm().
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* Reliable message transfer mode is used by default in SysCom.  This function
* provides the user the ability to modify this default for messages created by
* the calling EE. This allows the convenience of an EE-wide change in messaging
* transport mode without forcing a call to AaSysComMsgSetMtm() for each message
* created. Note that only messages created after the call to this function will
* be impacted by the change to the default transfer mode.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetMtm
*
* @par Example:
*   @code
*       AaSysComEeSetMtmDefault(EAaSysComMtm_Basic);
*       ...
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*   @endcode
*
*******************************************************************************/
void AaSysComEeSetMtmDefault(const EAaSysComMtm requestedTransferMode);

/**
********************************************************************************
*
* @brief      Get the default message transfer mode for messages created by the
*             EE.
*
* @return     The function returns the default message transfer mode.
*
* @par Description:
* The AaSysComEeGetMtmDefault() function reveals the EE-specific default message
* transfer mode.
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
* AaSysComEeSetMtmDefault
*
* @par Example:
*   @code
*       EAaSysComMtm trMode = EAaSysComMtm_Basic;
*       AaSysComEeSetMtmDefault(trMode);
*       ...
*       trMode = AaSysComEeGetMtmDefault();
*   @endcode
*
*******************************************************************************/
EAaSysComMtm AaSysComEeGetMtmDefault(void);

/**
********************************************************************************
*
*   @brief    Return memory pool id associated with SysCom message
*
*******************************************************************************/
i32 AaSysComMsgGetPoolId(const void *message);

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysCom */
/** @} */   /* dgUpCcsAaSysCom */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_IFAASYSCOM_H */
