/** @file
*   @brief Common AaSysCom API definitions
*   @copyright 2015 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef IF_COMMON_AASYSCOM_H
#define IF_COMMON_AASYSCOM_H

/*----------------------- DOXYGEN GROUPS -------------------------------------*/


/**
 *  @defgroup dgAaSysCom AaSysCom API
 *  @ingroup  dgBasicSystemSw
 *
 *
 * This service provides communication between CC&S EUs located in same or
 * different EEs / CEs. The service provides
 * - basic message handling i.e. creation, sending, receiving and deletion
 * - advanced message handling functions e.g. echoing, forwarding and relaying
 * - message transfer mode handling (reliable / non reliable)
 * - means to access user data (payload) of messages
 * - address handling functions
 * - message envelope (header and trailer) handling functions
 * - endianness support functionality for CC&S itself and for application
 * - user, link and hop registration and deregistration functions
 *
 */

/*@{*/
/*@}*/

 /** @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 *
 * Application Programming Interface.
 *
 * This service provides communication between CC&S EUs located in same or
 * different EEs / CEs. The service provides
 * - basic message handling i.e. creation, sending, receiving and deletion
 * - advanced message handling functions e.g. echoing, forwarding and relaying
 * - message transfer mode handling (reliable / non reliable)
 * - means to access user data (payload) of messages
 * - address handling functions
 * - message envelope (header and trailer) handling functions
 * - endianness support functionality for CC&S itself and for application
 * - user, link and hop registration and deregistration functions
 */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <CcsCommon.h>
#include <glo_def.h>
#include <TAaSysComSicad.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaPro.h>
#include <IfAaSem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AASYSCOM_IN_USE
# define AASYSCOM_IN_USE     /**< SysCom is in use definition. */
#endif /* AASYSCOM_IN_USE */

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Messages/IfAaSysCom_Msgs.h"
#include "IfAaSysCom_Sicad.h"
#endif

/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a message.
*
* @param[in]    messageId           Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    messageTarget       Specifies the targeted recipient of the
*                                   message.
*
* @return       A pointer to the handle of the new message. In case of errors
*               GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreate function reserves and prepares appropriate resources
* for the message. Message body (user payload area) remains undefined.
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
* AaSysComMsgCreateP, AaSysComMsgCreateReply, AaSysComMsgCreateX,
* AaSysComMsgCreateCopy, AaSysComMsgCreateCopyRe, AaSysComMsgCreateCopyTo,
* AaSysComMsgDestroy, AaSysComMsgSend
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = (TAaSysComMsgSize)sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreate(const TAaSysComMsgId messageId,
                        const TAaSysComMsgSize messagePayloadSize,
                        const TAaSysComSicad messageTarget);


/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a reply message.
*
* @param[in]    messageId           Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    repliedMessage      Points to the handle of a message, source
*                                   address of which specifies the targeted
*                                   recipient of the message.
*
* @return       The function returns a pointer to the handle of the new reply
*               message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateReply function reserves and prepares resources for
* the reply message, sender and receiver addresses of which are taken from the
* original message by swapping those.  Message body (user payload area)
* remains undefined.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p repliedMessage is \c GLO_NULL function does no action
* and \c GLO_NULL is returned.
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
*       void *replyMsgPtr = GLO_NULL;
*       void *originalMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = (TAaSysComMsgSize)sizeof(TestMessage);
*       ...
*       originalMsgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       replyMsgPtr = AaSysComMsgCreateReply(msgId, msgPayloadSize, originalMsgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateReply(const TAaSysComMsgId messageId,
                             const TAaSysComMsgSize messagePayloadSize,
                             const void *repliedMessage);


/**
********************************************************************************
*
* @brief          Free resources related to a message.
*
* @param[in,out]  message   Points to a pointer to the handle of the message.
*                           It is nulled by return.
*
* @return         The function returns nothing.
*
* @par Description:
* The AaSysComMsgDestroy function destroys the message and takes care of
* freeing related resources.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
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
* AaSysComMsgCreate, AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgDestroy(&msgPtr)
*   @endcode
*
*******************************************************************************/
void AaSysComMsgDestroy(void **message);


/**
********************************************************************************
*
* @brief      Get the application part of a message.
*
* @param[in]  message   Points to the handle of the message.
*
* @return     The function returns a pointer to the message application
*             part (user payload).
*
* @par Description:
* The AaSysComMsgGetPayload function reveals the message application part
* (user payload) of the user-specified message.
* \n In case \p message has empty payload (\ref AaSysComMsgGetPayloadSize
* returns \c 0) function returns undefined value.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgReceive, AaSysComMsgGetPayloadSize, AaSysComMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *payloadPtr = GLO_NULL;
*       char payloadString[] = "Hello world!";
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payloadPtr = AaSysComMsgGetPayload(msgPtr);
*       strcpy(payloadPtr, payloadString);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgGetPayload(const void *message);



/**
********************************************************************************
*
* @brief        Receive any message.
*
* @param[in]  maxTimeToWait Specifies the maximum time (in microseconds)
*                           a message is waited for. AASYSCOM_INFINITE_WAITTIME
*                           denotes infinite wait time and AASYSCOM_NO_WAITTIME
*                           denotes zero waitime. See also "USAGE" section.
*
* @return     The function returns a pointer to the handle of the received
*             message, if there is a message to be received, otherwise GLO_NULL
*             is returned. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgReceive function points the handle of the received message.
* Ownership of the message is transferred to the user.
*
* In case no SysCom message queue is existing yet, it will be created automatically.
* A warning will be issued as creation of the message queue should be the job of the
* instance creating the thread.
* In addition this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
* Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
* (layering of AaSysCom and AaPro).
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
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
* AaSysComMsgReceiveSelective, AaSysComMsgGetPayload, AaSysComMsgDestroy
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(1000);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgReceive(const u32 maxTimeToWait);


/**
********************************************************************************
*
* @brief          Send a message.
*
* @param[in,out]  message   Points to a pointer to the handle of the message.
*                           It is nulled by return.
*
* @return         The function returns nothing.
*
* @par Description:
* The AaSysComMsgSend function sends the message. Ownership of the message is
* transferred. Message is deleted in case of sending fails.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*   function does no action.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
*
* @par Usage:
* This function does not resolve the sender. Therefore
* \ref AaSysComMsgSetSender function must be called prior to calling this function.
* In case of errors (message cannot be delivered to the receiver for some
* reason) releasing the message and related resources is handled by the
* function.
* \n\b MCU: Linux environment supports sending messages from Linux native threads
* (threads not created via AaPro). In such case, sender should be set to
* \ref AASYSCOM_ADDRESS_ANY.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgCreate, AaSysComMsgSetSender
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       TAaSysComSicad msgSender = AaSysComSicadGet(OWN_CPID,
*                                                   AaSysComGetOwnNid());
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetSender(msgPtr, msgSender);
*       AaSysComMsgSend(&msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSend(void **message);


/**
********************************************************************************
*
* @brief          Send a message with parameter sender.
*
* @param[in,out]  message       Points to a pointer to the handle of the
*                               message. It is nulled by return.
*
* @param[in]      messageSender Specifies the sender of the message (SIC address
*                               of the source).
*
* @return         The function returns nothing.
*
* @par Description:
* The AaSysComMsgSendS function sends the message and fills message sender
* field. Ownership of the message is transferred. Message is released and
* related resources are freed by the function, in case sending fails.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*           function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*          function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \GLO_NULL
*           function behaves in undefined way and could lead to crash.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
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
* AaSysComMsgCreate, AaSysComMsgSetSender
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComSicad msgSender = AaSysComSicadGet(OWN_CPID,
*                                                   AaSysComGetOwnNid());
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgSendS(&msgPtr, msgSender);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSendS(void **message, const TAaSysComSicad messageSender);


/**
********************************************************************************
*
* @brief        Set the sender of a message.
*
* @param[in]    message         Points to the handle of the message.
*
* @param[in]    messageSource   Specifies the sender of the message.
*
* @return       The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetSender function overwrites the sender of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
*       TAaSysComSicad ownSicad = AaSysComSicadGet(OWN_CPID,
*                                                  AaSysComGetOwnNid());
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetSender(msgPtr, ownSicad);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetSender(const void *message,
                          const TAaSysComSicad messageSource);

/**
********************************************************************************
*
* @brief        Transfer the ownership of message to the caller.
*
* @param[in]    message  Points to the handle of the message.
*
* @return       The function returns nothing.
*
* @par Description:
* The AaSysComMsgTake function transfers the ownership of the user-specified
* message to the caller of the function.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: This function is Rel2 specific, and does no action.
*
* @par Usage:
* In general, software should be designed so that this function is not needed.
* In DSP side function is not needed at all - it is deprecated.
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
*       void *payloadPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payloadPtr = AaSysComMsgGetPayload(msgPtr);
*       AaSysComMsgTake(payloadPtr->tmpMsgPtr);
*       AaSysComMsgDestroy(&(payloadPtr->tmpMsgPtr));
*   @endcode
*
*******************************************************************************/
void AaSysComMsgTake(const void *message);


/**
********************************************************************************
*
* @brief      Get the message identifier of a message.
*
* @param[in]  message       Points to the handle of the message.
*
* @return     The function returns the message identifier (SIC message type
*             number) of the message.
*
* @par Description:
* The AaSysComMsgGetId function reveals the message identifer (SIC message
* type number) of the the user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c 0.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(msgPtr);
*   @endcode
*
*******************************************************************************/
TAaSysComMsgId AaSysComMsgGetId(const void *message);


/**
********************************************************************************
*
* @brief      Get the length of the application part of a message.
*
* @param[in]  message       Points to the handle of the message.
*
* @return     The function returns the size of the message application part
*             (user payload) in bytes.
*
* @par Description:
* The AaSysComMsgGetPayloadSize function reveals the size of the message
* application part (user payload) of the user-specified message.
*
* @par Errors:
* \b MCU: It is an error to call this function for a large message (a message
* for which \ref AaSysComMsgIsLarge returns \c GLO_TRUE). In such case
* respective error message is logged and \c 0 is returned.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c 0.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgReceive, AaSysComMsgIsLarge
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgSize payloadSize = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payloadSize = AaSysComMsgGetPayloadSize(msgPtr);
*   @endcode
*
*******************************************************************************/
TAaSysComMsgSize AaSysComMsgGetPayloadSize(const void *message);


/**
********************************************************************************
*
* @brief      Set the size of the payload of a message.
*
* @param[in]  message Points to a pointer to the handle of the message. Setting
*                     the size bigger than the current size may cause
*                     reallocation and copying of the message. In such case
*                     argument is updated by return.
*
* @param[in]  messagePayloadSize New payload size for the msg.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetPayloadSize function overwrites the payload size of the
* user-specified message. If the requested size is bigger than current size a
* new, larger message is created and filled with a copy of the current message,
* which is then destroyed. The content of payload not filled by copy remains
* undefined.
* If the requested size is lower than current size a new, smaller message is
* created and it is filled with a copy of the current message (up to new size)
* The old message is then destroyed.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
* - \b RT: Function not supported.
* - \b DSP: Implemented only for Rel2 (LBT2173). In case \p message is
* \c GLO_NULL or \p *message is \c GLO_NULL function does no action.
*
* @par Usage:
* Resetting the size may cause reallocation and copying of message. Use only
* when the possible consequences are taken into account.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgReceive, AaSysComMsgShrinkPayloadSize
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgSetPayloadSize(&msgPtr, sizeof(TestMessage));
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetPayloadSize(void **message,
                               const TAaSysComMsgSize messagePayloadSize);


/**
********************************************************************************
*
* @brief      Shrink the size of the payload of a message.
*
* @param[in]  message Points to a pointer to the handle of the message.
* @param[in]  payloadSize New payload size for the msg.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgShrinkPayloadSize function reduces the payload size of the
* user-specified message.
* Contrary to \ref AaSysComMsgSetPayloadSize, this function amends existing
* message and content of the payload (up to the new, smaller size) remains
* unchanged. Function does no action in case new payload size is not lower
* than actual payload size.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* Resetting the size may cause reallocation and copying of message. Use only
* when the possible consequences are taken into account.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgReceive, AaSysComMsgSetPayloadSize
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgShrinkPayloadSize(&msgPtr, sizeof(TestMessage));
*   @endcode
*
*******************************************************************************/
void AaSysComMsgShrinkPayloadSize(void **message,
                                  const TAaSysComMsgSize payloadSize);


/**
********************************************************************************
*
* @brief      Get the receiver of a message.
*
* @param[in]  message   Points to the handle of the message.
*
* @return     The function returns the address of the message receiver.
*
* @par Description:
* The AaSysComMsgGetReceiver function reveals the receiver of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c 0.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComSicad receiverSicad = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       receiverSicad = AaSysComMsgGetReceiver(msgPtr);
*   @endcode
*
*******************************************************************************/
TAaSysComSicad AaSysComMsgGetReceiver(const void *message);


/**
********************************************************************************
*
* @brief      Get the sender of a message.
*
* @param[in]  message   Points to the handle of the message.
*
* @return     The function returns the address of the message sender.
*
* @par Description:
* The AaSysComMsgGetSender function reveals the sender of the user-specified
* message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c 0.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgReceive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComSicad senderSicad = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       senderSicad = AaSysComMsgGetSender(msgPtr);
*   @endcode
*
*******************************************************************************/
TAaSysComSicad AaSysComMsgGetSender(const void *message);


/**
********************************************************************************
*
* @brief      Set the message identifier (SIC message type number) of a
*             message.
*
* @param[in]  message     Points to the handle of the message.
*
* @param[in]  messageId   Specifies the message identifier (SIC message type
*                         number) of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetId function overwrites the message identifier (SIC
* message type number) information of the user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could leads to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could leads to crash.
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
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgSetId(msgPtr, TEST_MSG);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetId(const void *message,
                      const TAaSysComMsgId messageId);

/**
********************************************************************************
*
* @brief      Set the message priority of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @param[in]  messagePriority Specifies the message priority of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetPriority function overwrites the message priority and also
* overwrites (invalidates) DSCP value of the user-specified message. This
* message priority has no impact on link priority which is controlled by
* \ref AaSysComSendViaLink or \ref AaSysComSendWithPriority.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: Function not supported.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* If intermediate gateways need to handle this message with priority then this
* API will set a bit on the message which is transmitted end-end. This is not
* the same as the EAaSysComSendPriority which only impacts links selection from
* the sending node. Please pay attention to use only one set of functions
* AaSysComMsgSetPriority and AaSysComMsgGetPriority or AaSysComMsgSetDscp and
* AaSysComMsgGetDscp for one message because DSCP value and message priority is
* saved in the same field. DSCP value overwrites message priority and similarly
* message priority overwrites DSCP value. Only one value can be valid/set.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetPriority, AaSysComMsgSetDscp, AaSysComMsgGetDscp, AaSysComMsgClearDscp
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetPriority(msgPtr, EAaSysComMsgPriority_High);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetPriority(const void *message,
                            const EAaSysComMsgPriority requestedPriority);

/**
********************************************************************************
*
* @brief      Get the message priority of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns the message priority.
*
* @par Description:
* The AaSysComMsgGetPriority function reveals the priority of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: Function not supported.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* Please pay attention to use only one set of functions AaSysComMsgSetPriority
* and AaSysComMsgGetPriority or AaSysComMsgSetDscp and AaSysComMsgGetDscp for
* one message because DSCP value and message priority is saved in the same
* field. DSCP value overwrites message priority and similarly message priority
* overwrites DSCP value. Only one value can be valid/set.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetPriority, AaSysComMsgSetDscp, AaSysComMsgGetDscp, AaSysComMsgClearDscp
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       EAaSysComMsgPriority messagePriority;
*       ...
*       msgPtr           = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       messasgePriority = AaSysComMsgGetPriority(msgPtr);
*   @endcode
*
*******************************************************************************/
EAaSysComMsgPriority AaSysComMsgGetPriority(const void *message);

/**
********************************************************************************
*
* @brief      Set the DSCP field of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @param[in]  dscp Specifies the DSCP value.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetDscp function overwrites the DSCP value and also overwrites
* (invalidates) message priority of the user-specified message. DSCP value has
* no impact on link priority which is controlled controlled by
* \ref AaSysComSendViaLink or \ref AaSysComSendWithPriority.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* \n In case dscp value is bigger than allowed (0x3F) function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* If intermediate gateways need to handle this message with priority then this
* API will set a bit on the message which is transmitted end-end. This is not
* the same as the EAaSysComSendPriority which only impacts links selection from
* the sending node. Please pay attention to use only one set of functions
* AaSysComMsgSetPriority and AaSysComMsgGetPriority or AaSysComMsgSetDscp and
* AaSysComMsgGetDscp for one message because DSCP value and message priority is
* saved in the same field. DSCP value overwrites message priority and similarly
* message priority overwrites DSCP value. Only one value can be valid/set.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetDscp, AaSysComMsgSetPriority, AaSysComMsgGetPriority, AaSysComMsgClearDscp
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       TAaSysComDscp dscp = TEST_DSCP;
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       if ( GLO_NULL != msgPtr )
*       {
*           AaSysComMsgSetDscp(msgPtr, dscp);
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetDscp(void * const message,
                        const TAaSysComDscp dscp);

/**
********************************************************************************
*
* @brief      Get the DSCP value of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @param[out] dscp     Points to an object containing the DSCP value of
*                      the message.
*
* @return     The function returns EAaSysComMsgGetDscpReturnCode_Ok if DSCP
*             value is set and valid, otherwise function returns
*             EAaSysComMsgGetDscpReturnCode_DscpNotSet.
*
* @par Description:
* The AaSysComMsgGetDscp function reveals the DSCP value of the user-specified
* message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL or \p dscp is \c GLO_NULL
* function returns EAaSysComMsgGetDscpReturnCode_DscpNotSet.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* Function returns DSCP value only if this value is set and valid.
* Please pay attention to use only one set of functions AaSysComMsgSetPriority
* and AaSysComMsgGetPriority or AaSysComMsgSetDscp and AaSysComMsgGetDscp for
* one message because DSCP value and message priority is saved in the same
* field. DSCP value overwrites message priority and similarly message priority
* overwrites DSCP value. Only one value can be valid/set.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetDscp, AaSysComMsgSetPriority, AaSysComMsgGetPriority, AaSysComMsgClearDscp
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       EAaSysComMsgPriority messagePriority;
*       EAaSysComMsgGetDscpReturnCode retVal;
*       TAaSysComDscp dscp;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       if ( GLO_NULL != msgPtr )
*       {
*           retVal = AaSysComMsgGetPriority(msgPtr, &dscp);
*       }
*   @endcode
*
*******************************************************************************/
EAaSysComMsgGetDscpReturnCode AaSysComMsgGetDscp(const void * const message,
                                                 TAaSysComDscp * const dscp);

/**
********************************************************************************
*
* @brief      Clear the DSCP fields of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgClearDscp function clears the DSCP value bits and DSCP valid bit.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: Function not supported.
*
* @par Usage:
* The function is used to clear all DSCP related bits.
* Please notice, after calling this function priority bits are cleared as well.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetDscp, AaSysComMsgGetDscp, AaSysComMsgSetPriority, AaSysComMsgGetPriority
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgClearDscp(msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgClearDscp(void * const message);

/**
********************************************************************************
*
* @brief      Set the message transfer mode of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @param[in]  requestedTransferMode Specifies the message transfer mode of
*                                   the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetMtm function overwrites the message transfer mode of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* Reliable message transfer mode is used by default in SysCom. Reliable mode
* should be prefered mode for most of SysCom messages. Setting message transfer
* mode to unreliable should be done only for unimportant messages.
* When using unreliable mode, underlaying link might not do any resending
* (retransmitting) at all.
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
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetMtm(msgPtr, EAaSysComMtm_Reliable);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetMtm(const void *message,
                       const EAaSysComMtm requestedTransferMode);

/**
********************************************************************************
*
* @brief      Get the message transfer mode of a message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns the message transfer mode.
*
* @par Description:
* The AaSysComMsgGetMtm function reveals the message transfer mode of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \ref EAaSysComMtm_Reliable.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* AaSysComMsgSetMtm
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       EAaSysComMtm trMode;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       trMode = AaSysComMsgGetMtm(msgPtr);
*   @endcode
*
*******************************************************************************/
EAaSysComMtm AaSysComMsgGetMtm(const void *message);


/**
********************************************************************************
*
* @brief      Set the receiver of a message.
*
* @param[in]  message         Points to a pointer to the handle of the message.
*
* @param[in]  messageTarget   Specifies the receiver of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetReceiver function overwrites the receiver of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
*       TAaSysComSicad msgReceiver = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgSetReceiver(&msgPtr, msgReceiver);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetReceiver(void **message,
                            const TAaSysComSicad messageTarget);

/**
********************************************************************************
*
* @brief      Reserve and prepare resources for a message pre-filled with a
*             copy of a user-specified message.
*
* @param[in]  originalMessage   Points to the handle of a message, which
*                               is copied into the message.
*
* @return     The function returns a pointer to the handle of the new,
*             pre-filled message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateCopy function reserves and prepares resources for the
* message and fills it with a copy of the original message.
*
* @par Errors:
* \b MCU: The returns \c GLO_NULL if \p originalMessage
* refers to a large message of payload size exceeding value returned from
* \ref AaSysComMsgGetMaxPayload.
*
* @par Restrictions:
* - \b MCU: In case \p originalMessage is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
* - \b RT: In case \p originalMessage is \c GLO_NULL function does no action
*  and returns \c GLO_NULL.
* - \b DSP: In case \p originalMessage is \c GLO_NULL function does no action
*  and returns \c GLO_NULL.
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
* AaSysComMsgCreate, AaSysComMsgCreateCopyRe, AaSysComMsgCreateCopyTo
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *copyMsgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       copyMsgPtr = AaSysComMsgCreateCopy(msgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateCopy(const void *originalMessage);


/**
********************************************************************************
*
* @brief      Reserve and prepare resources for a reply message pre-filled
*             with a copy of a user-specified message.
*
* @param[in]  originalMessage   Points to the handle of a message, which
*                               is copied into the new message.
*
* @param[in]  repliedMessage    Points to the handle of a message, source
*                               address of which specifies the targeted
*                               recipient of the message.
*
* @return     The function returns a pointer to the handle of the new,
*             pre-filled reply message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateCopyRe function reserves and prepares resources for
* the reply message and fills it with a copy of the original message. The
* receiver of the message is the sender of the user-specified replied message.
*
* @par Errors:
* \b MCU: The function returns \c GLO_NULL if
* \p originalMessage refers to a large message
* of payload size exceeding value returned from
* \ref AaSysComMsgGetMaxPayload.
*
* @par Restrictions:
* - \b MCU: In case \p originalMessage is \c GLO_NULL or \p repliedMessage
* is \c GLO_NULL function does no action and returns \c GLO_NULL.
* - \b RT: In case \p originalMessage is \c GLO_NULL or \p repliedMessage
* is \c GLO_NULL function does no action and returns \c GLO_NULL.
* - \b DSP: In case \p originalMessage is \c GLO_NULL or \p repliedMessage
* is \c GLO_NULL function does no action and returns \c GLO_NULL.
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
* @see AaSysComMsgCreateCopy
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *origMsgPtr = GLO_NULL;
*       void *repliedMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       origMsgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       repliedMsgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgPtr = AaSysComMsgCreateCopyRe(origMsgPtr, repliedMsgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateCopyRe(const void *originalMessage,
                              const void *repliedMessage);


/**
********************************************************************************
*
* @brief      Reserve and prepare resources for a message pre-filled with a
*             copy of a user-specified message.
*
* @param[in]  originalMessage   Points to the handle of a message, which is
*                               copied into the message.
*
* @param[in]  messageTarget     Specifies the targeted recipient of the
*                               message.
*
* @return     The function returns a pointer to the handle of the new,
*             pre-filled message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateCopyTo function reserves and prepares resources for
* the message and fills it with a copy of the original message into the
* message. The receiver of the message is the user-specified target.
*
* @par Errors:
* <b>MCU specific:</b><br> The function returns \c GLO_NULL
* if \p originalMessage refers to a large message
* of payload size exceeding value returned from
* \ref AaSysComMsgGetMaxPayload.
*
* @par Restrictions:
* - \b MCU: In case \p originalMessage is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
* - \b RT: In case \p originalMessage is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
* - \b DSP: In case \p originalMessage is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
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
* AaSysComMsgCreateCopy
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *origMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID_1, TEST_NID);
*       TAaSysComSicad newTarget = AaSysComSicadGet(TEST_CPID_2, TEST_NID);
*       ...
*       origMsgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       msgPtr = AaSysComMsgCreateCopyTo(origMsgPtr, newTarget);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateCopyTo(const void *originalMessage,
                              const TAaSysComSicad messageTarget);

/**
********************************************************************************
*
* @brief      Reserve and prepare resources for a message.
*
* @param[in]  messageId             Specifies the message id (SIC message type
*                                   number) of the message.
*
* @param[in]  messagePayloadSize    Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]  messageTarget         Specifies the targeted recipient of the
*                                   message.
*
* @param[in]  requestedTransferMode Specifies the message transfer mode to be
*                                   used.
*
* @param[in]  requestedLink         Specifies the communication point
*                                   identifier of the linkname to be used.
*
* @return     The function returns a pointer to the handle of the new message.
*             In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgCreateX function reserves and prepares resources for the
* message to be sent over the user-specified route using the user-specified
* transfer mode. Message body (user payload area) remains undefined.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* AaSysComMsgCreateX function must be used together with
* \ref AaSysComMsgSendViaLink function.
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
* AaSysComMsgCreate, AaSysComMsgSendViaLink
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       TAaSysComLinkId linkId = AASYSCOM_LINK_SRIO;
*       ...
*       msgPtr = AaSysComMsgCreateX(myMsgId,
*                                   msgPayloadSize,
*                                   msgTarget,
*                                   EAaSysComMtm_Basic,
*                                   linkId);
*       AaSysComMsgSendViaLink(&msgPtr,
*                              EAaSysComSendPriority_Unspecified,
*                              linkId);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateX(const TAaSysComMsgId messageId,
                         const TAaSysComMsgSize messagePayloadSize,
                         const TAaSysComSicad messageTarget,
                         const EAaSysComMtm requestedTransferMode,
                         const TAaSysComLinkId requestedLink);


/**
********************************************************************************
*
* @brief          Echo a message.
*
* @param[in,out]  message   Points to the pointer to the handle of the message.
*                           It is nulled by return.
*
* @return         The function returns nothing.
*
* @par Description:
* The AaSysComMsgEcho function sends the message back to the sender of it.
* Ownership of the message is transferred.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*           function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*          function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \GLO_NULL
*           function behaves in undefined way and could lead to crash.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
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
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgEcho(&msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgEcho(void **message);


/**
********************************************************************************
*
* @brief      Forward a message.
*
* @param[in]  message         Points to the pointer to the handle of the
*                             message. It is nulled by return.
*
* @param[in]  messageTarget   Specifies the new target of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgForward function refreshes the source address of the message
* and sends the updated message to the user-specified target. Ownership of the
* message is transferred.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*           function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*          function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \GLO_NULL
*           function behaves in undefined way and could lead to crash.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
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
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgForward(&msgPtr, msgTarget);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgForward(void **message,
                        const TAaSysComSicad messageTarget);


/**
********************************************************************************
*
* @brief      Receive a message of specific type.
*
* @param[in]  maxTimeToWait   Specifies the maximum time (in microseconds) a
*                             message is waited for. AASYSCOM_INFINITE_WAITTIME
*                             denotes infinite wait time and
*                             AASYSCOM_NO_WAITTIME denotes zero waitime.
*
* @param[in]  messageIdFilter Points to an array of accepted/rejected message
*                             identifiers (SIC message type numbers). First item
*                             in array must state the number of following
*                             identifiers. Positive sign of first item indicates
*                             that messages are accepted while negative sign
*                             indicates that messages are rejected. See example.
*
* @return     The function returns a pointer to the handle of the received
*             message, if there is a message to be received, otherwise GLO_NULL
*             is returned. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysComMsgReceiveSelective function points the handle of the received
* message, message identifier (SIC message type number) of which conforms to
* the user-specified rules. Ownership of the message is transferred to the
* user.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p messageIdFilter is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
*
* @par Usage:
* It is not recommended to use this function. Potential users are advised to
* consider using standard receiving function
* \ref AaSysComMsgReceive instead due to
* potential implementation specific performance issues.
* The actual wait time is implementation specific and is affected by wait time
* rounding and tick waiting time variation. If the requested wait time is
* shorter than one system tick, the actual wait time should equal to one system
* tick. Otherwise the wait time is rounded down to the system tick resolution.
* Receive returns to the caller when a message matching any of the specified
* message types is found. The first position in messageIdFilter contains the
* number of entries in the list that follows. Positive sign of first item
* indicates that messages are accepted while negative sign indicates that
* messages are rejected. If the number of entries is zero, all messages are
* accepted.
*
* In case no SysCom message queue is existing yet, it will be created automatically.
* A warning will be issued as creation of the message queue should be the job of the
* instance creating the thread.
* In addition this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
* Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
* (layering of AaSysCom and AaPro).
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
*       // receive only TEST_MSG's
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgIdFilter[] = {1, TEST_MSG};
*       ...
*       msgPtr = AaSysComMsgReceiveSelective(1000, msgIdFilter);
*   @endcode
*   @code
*       // receive only TEST_MSG1 and TEST_MSG2
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgIdFilter[] = {2, TEST_MSG1, TEST_MSG2};
*       ...
*       msgPtr = AaSysComMsgReceiveSelective(1000, msgIdFilter);
*   @endcode
*   @code
*       // receive all messages except TEST_MSG1 and TEST_MSG2
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgIdFilter[] = { -2, TEST_MSG1, TEST_MSG2 };
*       ...
*       msgPtr = AaSysComMsgReceiveSelective(1000, msgIdFilter);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgReceiveSelective(const u32 maxTimeToWait,
                                  const TAaSysComMsgId *messageIdFilter);


/**
********************************************************************************
*
* @brief      Relay a message.
*
* @param[in]  message         Points to the pointer to the handle of the
*                             message. It is nulled by return.
*
* @param[in]  messageTarget   Specifies the new target of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgRelay function preserves the source address of the message
* and sends the message to the user-specified target. Ownership of the message
* is transferred.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*           function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*          function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \GLO_NULL
*           function behaves in undefined way and could lead to crash.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
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
*       AaSysComMsgRelay(&msgPtr, msgTarget);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgRelay(void **message,
                      const TAaSysComSicad messageTarget);

/**
********************************************************************************
*
* @deprecated    This function is deprecated. Use AaSysComEuUserRegister
*                instead.
*
* @see           AaSysComEuUserRegister
*
*******************************************************************************/
TAaSysComCpid AaSysComUserRegister(const TAaSysComCpid userCpid,
                                   const u32 euId);

/**
********************************************************************************
*
* @brief        Register the user for current execution unit.
*
* @param[in]    userCpid  Specifies the communication point ID to be registered.
*
* @return       The function returns valid communication point ID in successful
*               case. Or AASYSCOM_CP_INVALID in case of error.
*
* @par Description:
* The AaSysComEuUserRegister function registers communication point ID for
* current execution unit. In order to be able to receive and send messages the
* user needs to register itself first.
*
* Registering a new user on active communication point removes the registration
* of the previous user.
* Does not increment user count if the same CPID was registered already.
*
* Communication point ID can be either static or dynamic. Static (predefined,
* well-known) CPIDs can be defined at design time but CPID to execution unit
* binding is done at run time via AaSysComUserRegister API. For example,
* static CPID can be used for server type of applications where CPID should be
* known to other services that will initiate communication. Static CPID is
* registered by providing some valid CPID value via userCpid parameter.
* Dynamic CPID can be used for applications for which CPID does not need to be
* known to other services (for example client applications that initiate
* communication with server). Dynamic CPID is registered by using
* \ref AASYSCOM_CP_INVALID value for userCpid parameter.
*
* In case no SysCom message queue is existing yet, it will be created automatically.
* A warning will be issued as creation of the message queue should be the job of the
* instance creating the thread.
* In addition this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
* Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
* (layering of AaSysCom and AaPro).
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
* AaSysComUserDeregister, AaSysComNumberOfUsersQuery, AaSysComUserListQuery
*
* @par Example:
*   @code
*       TAaSysComCpid cpid = AASYSCOM_CP_INVALID;
*       ...
*       cpid = AaSysComEuUserRegister(TASK_DSP_TEST);
*       if(cpid == TASK_DSP_TEST)
*       {
*           // Current EU ID successfully registered with static CPID
*       }
*   @endcode
*
*   @code
*       TAaSysComCpid cpid = AASYSCOM_CP_INVALID;
*       ...
*       cpid = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
*       if(cpid != AASYSCOM_CP_INVALID)
*       {
*           // Current EU ID successfully registered with dynamic CPID
*       }
*   @endcode
*
*******************************************************************************/
TAaSysComCpid AaSysComEuUserRegister(const TAaSysComCpid userCpid);



/**
********************************************************************************
*
* @brief          Deregister the user.
*
* @param[in]      userCpid  Specifies the communication point ID of the
*                           requesting user.
*
* @return         The function returns the communication point ID that was
*                 deregistered. If successful it equals to the user-specified
*                 communication point ID. Otherwise it is zero.
*
* @par Description:
* The AaSysComUserDeregister function deregisters the user.
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
*       TAaSysComCpid cPid = 0;
*       ...
*       cPid = AaSysComUserDeregister(TASK_DSP_TEST);
*       if(cPid == TASK_DSP_TEST)
*       {
*           //Deregisteration successful
*       }
*   @endcode
*
*******************************************************************************/
TAaSysComCpid AaSysComUserDeregister(const TAaSysComCpid userCpid);


/**
********************************************************************************
*
* @brief      Receive any message.
*
* @param[out]   messagePayload  Points to an object containing the message
*                               application part (user payload) of the
*                               received message.
*
* @param[out]   messagePayloadSize  Points to an object containing the size
*                                   of the message application part (user
*                                   payload) of the received message.
*
* @param[out]   messageId  Points to an object containing the message
*                          identifier (SIC message type number) of the
*                          received message.
*
* @param[out]   sourceAddress   Points to an object containing the source
*                               of the received message (SIC address of the
*                               sender).
*
* @param[out]   targetAddress   Points to an object containing the target
*                               of the received message (SIC address of the
*                               receiver).
*
* @param[in]    maxTimeToWait   Specifies the maximum time (in microseconds)
*                               a message is waited for.
*                               AASYSCOM_INFINITE_WAITTIME denotes infinite
*                               wait time and AASYSCOM_NO_WAITTIME denotes
*                               zero waitime. See also "USAGE" section.
*
* @return     The function returns a pointer to the handle of the received
*             message, if there is a message to be received, otherwise NULL is
*             returned. In case of errors NULL is returned.
*
* @par Description:
* The AaSysComMsgReceiveX function points the handle of the received message
* and passes on, as arguments of the function, message attributes. Ownership of
* the message is transferred to the user.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
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
* AaSysComMsgReceiveSelective, AaSysComMsgGetPayload, AaSysComMsgDestroy
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *msgPayloadPtr = GLO_NULL;
*       TAaSysComMsgSize msgPayloadSize;
*       TAaSysComMsgId msgId;
*       TAaSysComSicad srcSicad;
*       TAaSysComSicad destSicad;
*       ...
*       msgPtr = AaSysComMsgReceiveX(&msgPayloadPtr,
*                                    &msgPayloadSize,
*                                    &msgId,
*                                    &srcSicad,
*                                    &destSicad,
*                                    1000);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgReceiveX(void **messagePayload,
                          TAaSysComMsgSize *messagePayloadSize,
                          TAaSysComMsgId *messageId,
                          TAaSysComSicad *sourceAddress,
                          TAaSysComSicad *targetAddress,
                          const u32 maxTimeToWait);

/**
********************************************************************************
*
* @brief      Send a message with priority.
*
* @param[in]    message     Points to a pointer to the handle of the message.
*                           It is nulled by return.
*
* @param[in]    priority    Specifies the priority of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSendWithPriority function sends the message. If the
* underlying link supports prioritized sending of data, higher priority
* messages may be sent before lower priority messages. How priorities are
* handled is link-specific. Ownership of the message is transferred. In case of
* errors (message cannot be delivered to the receiver for some reason)
* releasing the message and related resources is handled by the function.
* This API has no impact on the message priority which is set by the
* \ref AaSysComMsgSetPriority API. This API only influences link selection from
* the sending node.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*   function does no action.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
*
* @par Usage:
* This function does not resolve the sender. Therefore AaSysComMsgSetSender
* function must be called prior calling this function.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgCreate, AaSysComMsgSend, AaSysComMsgSetSender
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSendWithPriority(&msgPtr,
*                                   EAaSysComSendPriority_Unspecified);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSendWithPriority(void **message,
                                 const EAaSysComSendPriority priority);

/**
********************************************************************************
*
* @brief      Query execution unit of a communication point.
*
* @param[in]  userCpid    Specifies the identifier of the communication point.
*
* @return     The function returns the execution unit identifier. If
*             unsuccessful (e.g. no such user is registered), zero is returned.
*
* @par Description:
* The AaSysComUserQueryEuid function reveals the execution unit identifier
* of the EU the user-specified communication point resides in.
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
* AaSysComUserQueryCb, AaSysComUserQueryName
*
* @par Example:
*   @code
*       TAaSysComCpid cpid = TEST_CPID;
*       u32 euId = 0;
*       ...
*       euId = AaSysComUserQueryEuid(cpid);
*   @endcode
*
*******************************************************************************/
u32 AaSysComUserQueryEuid(const TAaSysComCpid userCpid);

/**
********************************************************************************
*
* @brief      Deregister hop.
*
* @param[in]  hopId     Specifies the identifier of the hop to be deregistered.
*
* @return     The function returns the identifier of the hop that was
*             deregistered, if successful. Otherwise it returns zero.
*
* @par Description:
* The AaSysComHopDeregister function deregisters the user-specified hop.
* This means removing the association between a link and a destination address.
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
*       TAaSysComHopId hopId = 0;
*       ...
*       hopId = AaSysComHopDeregister(TEST_HOP_ID);
*       if(hopId == TEST_HOP_ID)
*       {
*           //Deregisteration successful
*       }
*   @endcode
*
*******************************************************************************/
TAaSysComHopId AaSysComHopDeregister(const TAaSysComHopId hopId);


/**
********************************************************************************
*
* @brief      Register hop.
*
* @param[in]  destinationAddress    Specifies the destination address for which
*                                   the hop is registered.
*
* @param[in]  metric                Specifies the relative preference of the
*                                   hop for the destination in question. 1
*                                   denotes first choice, 2 second, and so on.
*
* @param[in]  linkId                Specifies the link associated with the hop.
*
* @return     The function returns the identifier of the hop that was
*             registered, if successful. Otherwise it returns zero.
*
* @par Description:
* The AaSysComHopRegister function registers the user-specified hop. This
* means associating a link to a destination and giving it relative preference
* in case alternative routes are needed.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* Registering a hop with a link that has not been registered may cause
* malfunction and therefore should be avoided.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComHopDeregister
*
* @par Example:
*   @code
*       TAaSysComHopId hopId = 0;
*       TAaSysComLinkId linkId = TEST_LINK_ID;
*       TAaSysComSicad destSicad = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       hopId = AaSysComHopRegister(destSicad, 1, linkId);
*   @endcode
*
*******************************************************************************/
TAaSysComHopId AaSysComHopRegister(const TAaSysComSicad destinationAddress,
                                   const u32 metric,
                                   const TAaSysComLinkId linkId);

/**
********************************************************************************
*
* @brief      Deregister link.
*
* @param[in]  linkId    Specifies the identifier of the link.
*
* @return     The function returns the identifier of the link that was
*             deregistered, if successful. Otherwise it returns zero.
*
* @par Description:
* The AaSysComLinkDeregister function deregisters the user-specified link.
* This means removing the association between the link and the corresponding
* local communication point.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* Deregistering a link, which is associated to a destination address (by hop
* registration), may cause malfunction and therefore should be avoided.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComLinkRegister
*
* @par Example:
*   @code
*       TAaSysComLinkId linkId = 0;
*       ...
*       linkId = AaSysComLinkDeregister(TEST_LINK_ID);
*       if(linkId == TEST_LINK_ID)
*       {
*           //Deregisteration successful
*       }
*   @endcode
*
*******************************************************************************/
TAaSysComLinkId AaSysComLinkDeregister(const TAaSysComLinkId linkId);


/**
********************************************************************************
*
* @brief      Register link.
*
* @param[in]  linkId        Specifies the identifier of the link.
*
* @param[in]  cpid          Specifies the communication point identifier
*                           associated with the link.
*
* @param[in]  headerArea    Specifies the size of additional headers in bytes.
*
* @param[in]  trailerArea   Specifies the size of additional trailers in bytes.
*
* @param[in]  maxPduSize    Specifies the maximum size of a datagram that the
*                           link is capable of delivering.
*
* @return     The function returns the identifier of the link that was
*             registered, if successful. Otherwise it returns zero.
*
* @par Description:
* The AaSysComLinkRegister function registers the user-specified link.
* This means associating the link to a local communication point.
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
* AaSysComLinkDeregister
*
* @par Example:
*   @code
*       TAaSysComLinkId linkId = 0;
*       TAaSysComCpid cpid = TEST_CPID;
*       u32 headerArea = SIZE_OF_HEADERS;
*       u32 trailerArea = SIZE_OF_TRAILERS;
*       const u32 maxPduSize = MAX_DATAGRAM_SIZE;
*       ...
*       linkId = AaSysComLinkRegister(TEST_LINK_ID,
*                                     cpid,
*                                     headerArea,
*                                     trailerArea,
*                                     maxPduSize);
*       if(linkId == TEST_LINK_ID)
*       {
*           //Registeration successful
*       }
*   @endcode
*
*******************************************************************************/
TAaSysComLinkId AaSysComLinkRegister(const TAaSysComLinkId linkId,
                                     const TAaSysComCpid cpid,
                                     const u32 headerArea,
                                     const u32 trailerArea,
                                     const u32 maxPduSize);

/**
********************************************************************************
*
* @brief      Get the length of the SIC message.
*
* @param[in]  message     points to the handle of the message.
*
* @return     The function returns the size of the SIC message
*             (including header and possible trailer parts) in bytes.
*
* @par Description:
* The AaSysComSicMsgGetLength function reveals the total size of the
* SIC message of the user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c 0.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* This function is provided solely for handling integral SIC messages in link
* drivers and alike lower layer software.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComSicMsgGetMessage
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       u32 length = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       length = AaSysComSicMsgGetLength(msgPtr);
*   @endcode
*
*******************************************************************************/
u32 AaSysComSicMsgGetLength(const void *message);


/**
********************************************************************************
*
* @brief      Get the SIC message
*
* @param[in]  message     points to the handle of the message.
*
* @return     The function returns a pointer to the beginning of the SIC
*             message.
*
* @par Description:
* The AaSysComSicMsgGetMessage function reveals the SIC message of
* the user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* \n\b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
*
* @par Usage:
* This function is provided solely for handling integral SIC messages in link
* drivers and alike lower layer software.
* Typically application gets/has pointer to message handle, which can contain
* various information in addition to the message itself. The structure of
* abstract message handle is invisible for the application. Application must not
* assume that beginning of the message is the same as message handle.
* \ref AaSysComSicMsgGetMessage hides the structure of the handle and gets
* pointer to message itself.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComSicMsgGetLength
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *tmpMsgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       tmpMsgPtr = AaSysComSicMsgGetMessage(msgPtr);
*   @endcode
*
*******************************************************************************/
void* AaSysComSicMsgGetMessage(const void *message);

/**
********************************************************************************
*
* @brief      Sends the message via the users-specified link.
*
* @param[in, out]  message        Pointer to a pointer to the handle of the
*                                 message. It is nulled by return.
*
* @param[in]       priority       Priority of the link.
*
* @param[in]       requestedLink  Identifier of the link via which the message
*                                 will be sent.
*
* @return          None.
*
* @par Description:
* The AaSysComMsgSendViaLink function sends the message via the
* users-specified link. The function is used to bypass default routing.
* The priority provided is that of the link and has no impact on the
* message priority which is set only by \ref AaSysComMsgSetPriority.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
*   function does no action.
*
* \ref AASYSCOM_NODE_LOCAL usage:
* - \b MCU: Sending message to external node with
*           the \ref AASYSCOM_NODE_LOCAL alias as sender
*           is prohibited.
* - \b RT: No restrictions.
* - \b DSP: No restrictions.
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
* AaSysComMsgCreateX, AaSysComMsgSendS, AaSysComMsgSend, AaSysComMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       //FSPB DSP specific AIF link!
*       TAaSysComLinkId linkId = AASYSCOM_LINK_SRIO;
*       ...
*       msgPtr = AaSysComMsgCreateX(myMsgId,
*                                   msgPayloadSize,
*                                   msgTarget,
*                                   EAaSysComMtm_Basic,
*                                   linkId);
*       AaSysComMsgSendViaLink(&msgPtr,
*                              EAaSysComSendPriority_Unspecified,
*                              linkId);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSendViaLink(void **message,
                            const EAaSysComSendPriority priority,
                            const TAaSysComLinkId requestedLink);

/**
********************************************************************************
*
* @brief      Resets the application payload format of the message to
*             byte-oriented.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          None.
*
* @par Description:
* The AaSysComMsgSetApf2B function resets the application payload format of
* the message to EAaSysComMsgApf_8Big or EAaSysComMsgApf_8Little i.e. raw data
* message (byte-oriented) according to host endianness (sets the MAPF bits in
* the SICv1 message header).
* Note: only the MAPF bits of the header are set, the actual message payload
* remains intact.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* This function is used by message-specific marshalling (PrepareSend_XX)
* functions if the application message is defined as a normalized (raw data)
* message.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetApf, AaSysComMsgSetApf
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetApf2B(msgPtr);
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetApf2B(const void *message);


/**
********************************************************************************
*
* @brief      Resets the application payload format of the message.
*
* @param[in]  message Pointer to the handle of the message.
* @param[in]  apf     Message application payload format (MAPF) set to header.
*
* @return     None.
*
* @par Description:
* The AaSysComMsgSetApf function resets the application payload format of
* the message to requested value (i.e sets the MAPF bits in the SICv1 message
* header).
* Note: only the MAPF bits of the header are set, the actual message payload
* remains intact.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* This function is used by SysCom internally. It can also be used by
* message-specific marshalling (PrepareSend_XX) functions if the application
* message is defined as a normalized (raw data) message.
* SysCom sets default value and application overrides the default value in case
* of a byte-oriented messages.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetApf, AaSysComMsgSetApf2B
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetApf(msgPtr, EAaSysComMsgApf_32Little);
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetApf(const void *message, EAaSysComMsgApf apf);


/**
********************************************************************************
*
* @brief      Reveals the application payload format of the (received) message.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          The message application payload format (MAPF) of the
*                  message.
*
* @par Description:
* The AaSysComGetMsgApf function reveals the application payload format of
* the (received) message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c EAaSysComMsgApf_32Big.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* This function is used by SysCom internally. It can also be used by
* message-specific PrepareRead_XX (unmarshalling) functions if the application
* message is a word-aligned message containing non-word fields or the message is
* defined as a normalized (raw data) message.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetApf2B, AaSysComMsgSetApf
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       EAaSysComMsgApf msgApf;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgApf = AaSysComMsgGetApf(msgPtr);
*       ...
*   @endcode
*
*******************************************************************************/
EAaSysComMsgApf AaSysComMsgGetApf(const void *message);

/**
********************************************************************************
*
* @brief      Resets the message envelope format (MEF) of the message to
*             given value.
*
* @param[in]     message     Pointer to the handle of the message.
*
* @param[in]     mef         Message envelope format (MEF) to be set to header.
*
* @return        None.
*
* @par Description:
* The AaSysComMsgSetMef function resets the message envelope format (MEF) of
* the message to given format i.e. sets MEF bits in the SICv1 message header.
* This function is used internally by SysCom when creating a message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Reserved value can not be set. In case trailer is not allowed (compilation
* switch not set) '_Sicv1WithTrailer' is not allowed. In case illegal value is
* requested to be set, the function gives warning and returns without changing
* the MEF flags.
* \n In case \p message is \c GLO_NULL function does no action.
*
* @par Usage:
* This function is used internally by SysCom.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetMef
*
* @par Example:
*   @code
*       SMsgData *msg = GLO_NULL;
*       msg = (SMsgData*)RTOS_msgBufAlloc(sizeof(STestMsg), TEST_MSG_ID);
*       if(msg != GLO_NULL)
*       {
*         ...
*         AaSysComMsgSetMef((void*)msg, EAaSysComMsgMef_Sicv1WithTrailer);
*         ...
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetMef(const void *message, EAaSysComMsgMef mef);


/**
********************************************************************************
*
* @brief      Reveals the message envelope format of the (received) message.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          The message envelope format (MEF) of the message.
*
* @par Description:
* The AaSysComMsgGetMef function reveals the message envelope format of
* the (received) message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \ref EAaSysComMsgMef_NMAP.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* This function is used internally by SysCom when checking the format of the
* message envelope in receiving end.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetMef
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       EAaSysComMsgMef mef;
*
*       message = AaSysComMsgReceive(1000);
*       if(message != GLO_NULL)
*       {
*         mef = AaSysComMsgGetMef(message));
*         ...
*       }
*   @endcode
*
*******************************************************************************/
EAaSysComMsgMef AaSysComMsgGetMef(const void *message);


/**
********************************************************************************
*
* @brief      Gets the trailer of a message.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          Pointer to the trailer of the message.
*
* @par Description:
* The AaSysComMsgGetTrailer function reveals the trailer of the message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c GLO_NULL.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
*
* @par Usage:
* Used internally by SysCom when setting the trailer fields in a message to be
* sent or checking the trailer fields of received message.
*
* @par Rationale:
* None.

* @par Future directions:
* None.
*
* @see
* None
*
* @par Example:
*   @code
*       void *msg;
*       void *trailerPtr;
*       ...
*       msg = (SMsgData*)RTOS_msgBufAlloc(sizeof(STestMsg), TEST_MSG_ID);
*       if(msg != GLO_NULL)
*       {
*         ...
*         AaSysComMsgSetMef((void*)msg, EAaSysComMsgMef_Sicv1WithTrailer);
*         trailerPtr = AaSysComMsgGetTrailer(msgPtr);
*         ...
*       }
*         ...
*   @endcode
*
*******************************************************************************/
void* AaSysComMsgGetTrailer(const void *message);


/**
********************************************************************************
*
* @brief     Reveals the TTL field of a message trailer.
*
* @param[in]       message        Pointer to the handle of the message.
*
* @return          The TTL (Time To Live) field from the message trailer.
*
* @par Description:
* The AaSysComMsgGetTtlValue function reveals the Time To Live (TTL) field of
* the trailer of a message. In case trailer is not allowed in the SysCom
* messaging, this function returns the initial value (\ref AASYSCOM_DEFAULT_TTL) of
* TTL.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p message is \c GLO_NULL function does no action and returns
* \ref AASYSCOM_DEFAULT_TTL.
*
* @par Usage:
* This function is used internally by SysCom when current value of the TTL field
* is needed (for example checking if message is looping).
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgSetMef
*
* @par Example:
*   @code
*       void *msgPtr;
*       u16 ttl;
*
*       msgPtr = AaSysComMsgReceive(1000);
*       if(msgPtr != GLO_NULL)
*       {
*         ttl = AaSysComMsgGetTtlValue(msgPtr);
*         ...
*       }
*   @endcode
*
*******************************************************************************/
u8 AaSysComMsgGetTtlValue(const void *message);


/**
********************************************************************************
*
* @brief      Resets Time To Live (TTL) field of a message trailer to
*             given value.
*
* @param[in]     message     Pointer to the handle of the message.
*
* @param[in]     ttl         Time To Live (TTL) value to be set to trailer.
*
* @return        None.
*
* @par Description:
* The AaSysComMsgSetTtlValue function resets the Time To Live (TTL) of
* the message trailer to given value.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p message is \c GLO_NULL function does no action.
*
* @par Usage:
* This function is used internally by SysCom when creating a message.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgGetTtlValue, AaSysComMsgIsCrcOk
*
* @par Example:
*   @code
*       SMsgData *msg = GLO_NULL;
*
*       msg = (SMsgData*)RTOS_msgBufAlloc(sizeof(STestMsg), TEST_MSG_ID);
*       if(msg!=GLO_NULL)
*       {
*         AaSysComMsgSetTtlValue(msg, AASYSCOM_DEFAULT_TTL);
*         ...
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetTtlValue(const void *message, u8 ttl);


/**
*******************************************************************************
*
* @brief  Checks Time To Live (TTL) bits in message trailer flags.
*
* @param[in] message  Pointer to message handle.
*
* @return Decremented TTL value if trailer included TTL and TTL is in use.
*         Otherwise returns default TTL value.
*
* @par Description:
* AaSysComMsgCheckTtl checks if message envelope contains trailer and if
* Loop Detection is On (LDO). If so decrements Time To Live (TTL) bits in
* message trailer flags (TF1.TTL). Returns the decremented value of TTL.
*
* @par Errors:
* None
*
* @par Restrictions:
* In case \p message is \c GLO_NULL function does no action and returns
* \ref AASYSCOM_DEFAULT_TTL.
*
* @par Usage:
* The function is used by SysCom internally when sending a message outside node
* to determine if message is looping forever. When returned value is zero the
* message should be interpreted as looping message and should not be sent
* further anymore.
*
* @par Rationale:
* None
*
* @par Future directions:
* None
*
* @see
* None
*
* @par Example:
*   @code
*       void *msgPtr;
*       u8 ttl;
*
*       msgPtr = AaSysComMsgReceive(1000);
*       if(msgPtr != GLO_NULL)
*       {
*         ttl = AaSysComMsgCheckTtl(msgPtr);
*         if (0 == ttl)
*         {
*           ...
*         }
*         ...
*       }
*   @endcode
*
******************************************************************************/
u8 AaSysComMsgCheckTtl(const void *message);


/**
*******************************************************************************
*
* @brief  Calculates the CRC and compares it to CRC set in message trailer.
*
* @param[in] message  pointer to message
*
* @return GLO_TRUE if the CRC is correct.
*         GLO_FALSE if CRC is NOT correct.
*
* @par Description:
* AaSysComMsgIsCrcOk checks if message envelope contains trailer and if Error
* Detection is On (EDO). If so calculates the CRC of the message and checks if
* it matches with CRC set in trailer.
* Returns true if the CRC is correct. Returns false if CRC is not correct or if
* the message does not contain trailer at all or CRC is not used.
*
* @par Errors:
* None
*
* @par Restrictions:
* In case \p message is \c GLO_NULL function does no action and returns
* \c GLO_TRUE.
*
* @par Usage:
* The function is used by SysCom internally when receiving a message.
*
* @par Rationale:
* None
*
* @par Future directions:
* None
*
* @see
* None
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       if (!AaSysComMsgIsCrcOk(message))
*       {
*         // trace error situation
*       }
*   @endcode
*
******************************************************************************/
TBoolean AaSysComMsgIsCrcOk(const void *message);

/**
********************************************************************************
*
* @brief      Reorders the bytes of each 64-bit long field to local host format
*             if the endianness of the word-aligned message, defined by the
*             MAPF bits in the SICv1 message header, is opposite to host
*             endianness.
*
*
* @deprecated  This function should not be used as originally planned, since
*              64-bit long fields in word-oriented messages must be split to
*              separate 32-bit long fields and must be written/read by
*              application separately using respective services (see below).
*
* @param[in]       message        Pointer to the handle of the message.
*
* @param[in]       firstField     Pointer to the first of the consecutive
*                                 64-bit fields.
*
* @param[in]       numberOfFields Number of consecutive 64-bit fields.
*
* @par Description:
* The AaSysComEnd64ToHost function reorders the bytes of each 64-bit long
* field to local host format if the endianness of the word-aligned message,
* defined by the MAPF bits in the SICv1 message header, is opposite to host
* endianness. This function is used by message-specific unmarshalling
* (PrepareRead_XX) functions if the application message is a word-aligned
* message containing doubleword (64 bit) fields.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: Function not supported.
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
* AaSysComExtend32To64, AaSysComLSWof64, AaSysComMSWof64
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       u64 *firstFieldToBeSwapped = GLO_NULL;
*       u32 numberOfFields = 10;
*       void *payload = GLO_NULL;;
*
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payload = AaSysComMsgGetPayload(msgPtr);
*       firstFieldToBeSwapped = &(STestMessage *)payload->firstu64Field);
*       AaSysComEnd64ToHost(msgPtr,
*           (void*)firstFieldToBeSwapped,
*           numberOfFields);
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComEnd64ToHost(const void *message,
                         const void *firstField,
                         const u32 numberOfFields);


/**
********************************************************************************
*
* @brief      Reorders the bytes of the byte string field to local host format
*             if the endianness of the word-aligned message, defined by the
*             MAPF bits in the message header, is opposite to host endianness.
*
* @deprecated  This function should not be used as originally planned, since
*              bytestring fields in word-oriented messages must be written/read
*              by application separately using respective 'raw data' services
*              (see below).
*
* @param[in]       message        Pointer to the handle of the message.
*
* @param[in]       firstByte      Pointer to the first byte in the byte string.
*
* @param[in]       numberOfBytes  Number of bytes in the byte string.
*
* @par Description:
* The AaSysComEndBytesToHost function reorders the bytes of the byte string
* field to local host format if the endianness of the word-aligned message,
* defined by the MAPF bits in the message header, is opposite to host
* endianness. This function is used by messages-specific unmarshalling
* (PrepareRead_XX) functions if the application message is a word-aligned
* message containing byte strings.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: Function not supported.
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
* AaSysComGetRawData, AaSysComSetRawData
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *firstByte = GLO_NULL;
*       u32 numberOfBytes = 16;
*
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payload = AaSysComMsgGetPayload(msgPtr);
*       firstByte = &(STestMessage *)payload->firstByteField);
*       AaSysComEndBytesToHost(msgPtr, firstByte, numberOfBytes);
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComEndBytesToHost(const void *message,
                            const void *firstByte,
                            const u32 numberOfBytes);


/**
********************************************************************************
*
* @brief      Reverses the order of bytes of each 16-bit long field.
*
* @param[in]       firstField        Pointer to the first of the consecutive
*                                    16-bit fields.
*
* @param[in]       numberOfFields    Number of consecutive 16-bit fields.
*
* @par Description:
* The AaSysComEnd16Swap function reverses the order of bytes of each 16-bit
* long field. This function is used by message-specific PrepareSend_XX
* (marshalling) and PrepareRead_XX (unmarshalling) functions if the application
* message is defined as a byte oriented (i.e. normalized) message and it
* contains halfword (16 bit) fields.
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
*       void *payload = GLO_NULL;
*       void *firstField = GLO_NULL;
*       u32 numberOfFields = 10;
*
*       ...
*       payload = AaSysComMsgGetPayload(msgPtr);
*       firstField = &(STestMessage *)payload->firstu16Field);
*       AaSysComEnd16Swap(firstField, numberOfFields);
*   @endcode
*
*******************************************************************************/
void AaSysComEnd16Swap(const void *firstField, const u32 numberOfFields);


/**
********************************************************************************
*
* @brief      Reverses the order of bytes of each 32-bit long field.
*
* @param[in]       firstField        Pointer to the first of the consecutive
*                                    32-bit fields.
*
* @param[in]       numberOfFields    Number of consecutive 32-bit fields.
*
* @par Description:
* The AaSysComEnd32Swap function reverses the order of bytes of each 32-bit
* long field. This function is used by message-specific PrepareSend_XX
* (marshalling) and PrepareRead_XX (unmarshalling) functions if the application
* message is defined as a byte oriented (i.e. normalized) message and it
* contains word (32 bit) fields.
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
*       void *payload = GLO_NULL;
*       void *firstField = GLO_NULL;
*       u32 numberOfFields = 10;
*
*       ...
*       payload = AaSysComMsgGetPayload(msgPtr);
*       firstField = &(STestMessage *)payload->firstu32Field);
*       AaSysComEnd32Swap(firstField, numberOfFields);
*   @endcode
*
*******************************************************************************/
void AaSysComEnd32Swap(const void *firstField, const u32 numberOfFields);


/**
********************************************************************************
*
* @brief      Reverses the order of bytes of each 64-bit long field.
*
* @param[in]       firstField        Pointer to the first of the consequtive
*                                    64-bit fields.
*
* @param[in]       numberOfFields    Number of consequtive 64-bit fields.
*
* @par Description:
* The AaSysComEnd64Swap function reverses the order of bytes of each 64-bit
* long field. This function is used by message-specific PrepareSend_XX
* (marshalling) and PrepareRead_XX (unmarshalling) functions if the application
* message is defined as a byte oriented (i.e. normalized) message and it
* contains doubleword (64 bit) fields.
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
*       void *payload = GLO_NULL;
*       void *firstField = GLO_NULL;
*       u32 numberOfFields = 10;
*
*       ...
*       payload = AaSysComMsgGetPayload(msgPtr);
*       firstField = &(STestMessage *)payload->firstu64Field);
*       AaSysComEnd64Swap(firstField, numberOfFields);
*   @endcode
*
*******************************************************************************/
void AaSysComEnd64Swap(const void *firstField, const u32 numberOfFields);

/**
********************************************************************************
*
* @brief      Changes the order of bytes in word-oriented message to host
*             format.
*
* @param[in, out]   message   Pointer to pointer to the handle of the message.
*                             It is nulled in case of error in message length.
*
* @par Description:
* The AaSysComWordOrientedMsgToHost function checks the format (endianness)
* of received message by reading MAPF bits in the message header. If needed
* i.e. if the format of the message is different than host endiannes, reorders
* the bytes of each word of word-aligned message and sets the MAPF flags
* accordingly. The function first checks if length of a word-oriented message
* is correct i.e. divisible by 4 - if not the message is destroyed and log
* written.
* If the message is raw data message (byte oriented) nothing is done.
* This function is used by SIC link adapter when receiving a message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
* - \b RT: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
* - \b DSP: In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
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
* AaSysComWordOrientedMsgToBig
*
* @par Example:
*   @code
*       void *message;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComWordOrientedMsgToHost(&message);
*       if (GLO_NULL == message)
*       {
*         // message was Destroyed - nothing to do
*       }
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComWordOrientedMsgToHost(void **message);


/**
********************************************************************************
*
* @brief   If message is in final target changes the order of bytes to host
*          format.
*
* @param[in, out]    message   Pointer to pointer to the handle of the message.
*
* @par Description:
* The AaSysComIfFinalTargetSwapToHost function checks if the message is
* targeted to this node. If it is and it is a word-oriented message, the byte
* order of the message paylaod is set to host format (endianness) and the
* message application payload format (MAPF) flags are set respectively.
* If the message is not targeted to this node or the message payload format is
* byte-oriented (irrespective of the endianness), nothing is done.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
*
* @par Usage:
* The function is used by SysCom internally to convert word-oriented message in
* the final destination node to host format.
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
*       void *message;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComIfFinalTargetSwapToHost(&message);
*       if (GLO_NULL == message)
*       {
*         // the message was destroyed - nothing to do
*       }
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComIfFinalTargetSwapToHost(void **message);


/**
********************************************************************************
*
* @brief      Swaps the order of two consecutive words.
*
* @deprecated  This function should not be used as originally planned, since
*              64-bit long fields in word-oriented messages must be split to
*              separate 32-bit long fields and must be written/read by
*              application separately using respective services (see below).
*
* @param[in]   startPtr    Pointer to the first word.
*
* @par Description:
* The AaSysComMsgSwapTwoConsecutiveWords function swaps contents of two
* consecutive words. The operation is done byte by byte by swapping
* contents of first bytes then second bytes, third... and finally last (fourth)
* bytes.
* This function is used by message specific marshalling (PrepareSend_XX) /
* unmarshalling (PrepareRead_XX) funcions called by application when ordering
* e.g. contents of a u64 variable in a word-aligned message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p startPtr is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: Function not supported.
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
* AaSysComExtend32To64, AaSysComLSWof64, AaSysComMSWof64,
* (AaSysComMsgMultiSwapTwoConsecutiveWords)
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       TAaSysComMsgId msgId;
*       STestMsg *testMsg = GLO_NULL;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(message);
*       if (msgId == TEST_MSG_ID)
*       {
*         testMsg = (STestMsg *) AaSysComMsgGetPayload(message);
*         AaSysComMsgSwapTwoConsecutiveWords((void*)&(testMsg->firstWord));
*         ...
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSwapTwoConsecutiveWords(void * startPtr);


/**
********************************************************************************
*
* @brief      Swaps the order of multiple pairs of consecutive words.
*
* @deprecated  This function should not be used as originally planned, since
*              64-bit long fields in word-oriented messages must be split to
*              separate 32-bit long fields and must be written/read by
*              application separately using respective services (see below).
*
* @param[in]   startPtr    Pointer to the first word.
*
* @param[in]   numOfPairs  Number of word pairs to be swapped
*
* @par Description:
* The AaSysComMsgMultiSwapTwoConsecutiveWords function swaps contents
* of multiple pairs of consecutive words. The operation is done swapping one
* pair at a time using \ref AaSysComMsgSwapTwoConsecutiveWords function.
* This function is used by message specific marshalling(PrepareSend_XX) /
* unmarshalling (PrepareRead_XX) funcions called by application when ordering
* e.g. contents of multiple consecutive u64 variables in a word-aligned
* message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p startPtr is \c GLO_NULL function does no action.
* - \b RT: Function not supported.
* - \b DSP: Function not supported.
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
* AaSysComMsgSwapTwoConsecutiveWords
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       TAaSysComMsgId msgId;
*       STestMsg *testMsg = GLO_NULL;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(message);
*       if (msgId == TEST_MSG_ID)
*       {
*         testMsg = (STestMsg *) AaSysComMsgGetPayload(message);
*         AaSysComMsgMultiSwapTwoConsecutiveWords(
*             (void*)&(testMsg->firstWord),
*             3);
*         ...
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgMultiSwapTwoConsecutiveWords(void *startPtr, u32 numOfPairs);


/**
********************************************************************************
*
* @brief      Puts n bytes of raw data to given destination (message
*             parameter).
*
* @param[out] msgData          Pointer to the start of destination area in the
*                              message.
*
* @param[in] applicationData  Pointer to the first byte of the source byte
*                             string.
*
* @param[in] length           Number of bytes to be copied.
*
* @par Description:
* The AaSysComSetRawData function copies n bytes of raw data to the
* destination, which should be message parameter. The msgData byte raw data is
* set to BIG endian i.e. network endian format, which means that in BIG endian
* environment the function just copies the data and in LITTLE endian
* environment the data is reordered in 4 byte (u32) groups. Even if length of
* the byte string is not divisible by 4 the function handles the end of the
* string as it would be - length is rounded up to next number divisible with 4.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Length of the handled byte string must be divisible by 4 (or the message
* to which the data is set must contain padding after the string).
*
* @par Usage:
* Please note that the data to be copied can be any byte oriented data. E.g.
* in case of a ASCII string the application must take care of NUL end
* delimiter.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComGetRawData
*
* @par Example:
*   @code
*       STestMsg *testMsg = GLO_NULL;
*       u8 testByteString[16] = "Test string !";
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       testMsg = (STestMsg *)AaSysComMsgGetPayload(msgPtr);
*       AaSysComSetRawData((void*)testMsg->byteString,
*                          (void*)testByteString,
*                          (u32)sizeof(testByteString));
*         ...
*   @endcode
*
*******************************************************************************/
void AaSysComSetRawData(void *msgData,
                        void *applicationData,
                        u32 length);


/**
********************************************************************************
*
* @brief      Gets n bytes of raw data from given position (message parameter).
*
* @param[in]  msgData          Pointer to the start of source area in the
*                              message.
*
* @param[out]  applicationData  Pointer to the destination data area.
*
* @param[in]  length           Number of bytes to be copied.
*
* @par Description:
* The AaSysComGetRawData function copies n bytes of raw data from a message
* parameter to application area. The msgData is expected to be in BIG endian
* i.e. network endian format, which means that in BIG endian environment the
* function just copies the data and in LITTLE endian environment the data is
* reordered in 4 byte (u32) groups. Even if length of the byte string is not
* divisible by 4 the function handles the end of the string as it would be -
* length is rounded up to next number divisible with 4.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Length of the handled byte string must be divisible by 4 (or the message
* from which the data is get must contain padding after the string).
*
* @par Usage:
* Please note that the data to be copied can be any byte oriented data. E.g.
* in case of a ASCII string the message must contain the NUL end delimiter.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComSetRawData
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       TAaSysComMsgId msgId;
*       STestMsg *testMsg = GLO_NULL;
*       u8 testByteString[16];
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(message);
*       if (TEST_MSG_ID == msgId)
*       {
*         testMsg = (STestMsg *) AaSysComMsgGetPayload(message);
*         AaSysComGetRawData((void*)testMsg->byteString,
*                            (void*)testByteString,
*                            (u32)sizeof(testByteString));
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComGetRawData(void *msgData,
                        void *applicationData,
                        u32 length);


/**
********************************************************************************
*
* @brief    Checks if endianness of host cpu and message payload is same.
*
* @param[in]  message         Pointer to the handle of the message.
*
* @return   GLO_TRUE if the host endianness and endianness of the message payload
*           are same.
*           GLO_FALSE if endianness is not same.
*
* @par Description:
* The AaSysComIsHostAndMsgEndianSame function checks if host endianness and
* endianness of the message payload is same. Endianness is considered to be the
* same if CCS_LITTLE_ENDIAN is defiend and MAPF of the message is 32Little or
* 8Little or CCS_BIG_ENDIAN is defiend and MAPF of the message is 32Big or
* 8Big.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function does no action
* and returns \c GLO_FALSE.
* - \b RT: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
* - \b DSP: In case \p message is \c GLO_NULL
* function behaves in undefined way and could lead to crash.
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
* None
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       TAaSysComMsgId msgId;
*       STestMsg *testMsg = GLO_NULL;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(message);
*       if (TEST_MSG_ID == msgId)
*       {
*         testMsg = (STestMsg *)AaSysComMsgGetPayload(message);
*         if(GLO_FALSE == AaSysComIsHostAndMsgEndianSame((const void*)message))
*         {
*           // host and message endianness not same - do something
*           ...
*         }
*       }
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComIsHostAndMsgEndianSame(const void *message);


/**
********************************************************************************
*
* @brief      Reorders the bytes in byte string (byte array).
*
* @param[in]  message  Pointer to the message.
*
* @param[in] startPtr  Pointer to the first byte of the string to be reordered.
*
* @param[in] length    Number of bytes to be swapped.
*
* @par Description:
* The AaSysComMsgByteStringSwap function reorders bytes of a byte string in a
* message. Ordering is done in four byte (u32) groups. The byte string is
* handled in groups of 4 bytes. Even if length of the byte string is not
* divisible by 4 the function handles the end of the string as it would be -
* there must be padding after the string to justify the length. This function
* is needed if a word-aligned message contains byte-string. In that case SysCom
* reorders contents of the whole message and application interface must reorder
* the byte-string back. From SysCom point of view preferable way to do would be
* to define the message as raw data message and swap non-byte fields of the
* message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* This function does not check the MAPF flags from message header. So user of
* this function must be sure what it does !
* \n In case \p message is \c GLO_NULL or \p startPtr is \c GLO_NULL function
* does no action.
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
* None
*
* @par Example:
*   @code
*       void *message = GLO_NULL;
*       TAaSysComMsgId msgId;
*       STestMsg *testMsg = GLO_NULL;
*
*       message = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgId = AaSysComMsgGetId(message);
*       if (msgId == TEST_MSG_ID)
*       {
*         testMsg = (STestMsg *) AaSysComMsgGetPayload(message);
*         AaSysComMsgByteStringSwap(message,
*                                   &(testMsg->byteString),
*                                   BYTE_STRING_LEN_IN_TEST_MSG);
*         ...
*       }
*   @endcode
*
*******************************************************************************/
void AaSysComMsgByteStringSwap(void *message,
                               void *startPtr,
                               u32 length);

/**
********************************************************************************
*
* @brief      Gives the number of registered communication points (cpIds) in the node.
*
* @return     The function returns the current number of registered
*             communication points  in the node. If unsuccessful,
*             zero is returned.
*
* @par Description:
* The AaSysComNumberOfUsersQuery function returns the number of registered
* communication point users in the node.
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
* AaSysComUserRegister, AaSysComUserDeregister, AaSysComUserListQuery
*
* @par Example:
*   @code
*       u32 numRegisteredCpids;
*       numRegisteredCpids = AaSysComNumberOfUsersQuery();
*   @endcode
*
*******************************************************************************/
u32 AaSysComNumberOfUsersQuery(void);


/**
********************************************************************************
*
* @brief         Gives registered CPIDs in the node.
*
* @deprecated    Unsafe. Use AaSysComUserListQuery intead.
*                Caller has to reserve adequate space and extra for the array.
*                If a dynamic CPID is registered in the meantime, the array
*                will overflow.
* @see           AaSysComUserListQuery
*
*******************************************************************************/
void AaSysComUsersQuery(void *userCpids);

/**
********************************************************************************
*
* @brief      Gives registered communication points (cpIds) in the node.
*
* @param         userCpIds    Pointer to memory array for up to 'userMax' u32
*                             values where the registered CPID numbers are written.
*                             Notice that the ID numbers are returned on u32 data size.
*
* @param[in]     maxItems     Max number of u32 values that can be written on
*                             the array pointed by 'cpIds'.
*
* @return        The function returns the number in CPIDs read.
*                This is the number of users returned, and may be different from
*                the number of users at a given moment.
*
* @par Description:
* The AaSysComUserListQuery function returns the registered communication
* points in the node.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* This function can be used to query the users registered to syscom node
* with \ref AaSysComUserRegister. The information returned with this function
* equals to the \ref AASYSCOM_USERS_IN_NODE_REQ_MSG request and
* \ref AASYSCOM_USERS_IN_NODE_RESP_MSG, response, which shall remain the primary
* access method.
*
* Notice that the ID numbers are returned on u32 data size. This is the
* same size with \ref AASYSCOM_USERS_IN_NODE_RESP_MSG.
*
* Caller has to reserve adequate space for the array. Before calling this
* method the caller can request number of registered users with
* \ref AaSysComNumberOfUsersQuery function.
*
* Please note that extra space should be reserved: if the amount of dynamic
* users increases between these calls the array may be too small, and the
* last users (in the ascending CPID order) are left out.
* Hint: Always allocate some extra, or up to the max number of CPIDs.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComNumberOfUsersQuery
*
* @par Example:
*   @code
*       u32 *userCpIds = GLO_NULL;
*       u32 maxItems;
*       u32 userCount;
*       ...
*       maxItems  = AaSysComNumberOfUsersQuery() + 1;  // add extra space for one
*       userCpIds = (u32 *) malloc(maxItems * sizeof(u32));
*       userCount = AaSysComUserListQuery(userCpIds, maxItems);
*       ...
*       free(userCpIds);
*   @endcode
*
*******************************************************************************/
u32 AaSysComUserListQuery(u32 *userCpIds, const u32 maxItems);

/**
********************************************************************************
*
* @brief      Registers client for communication error notification.
*
* @param[in]  client    Specifies sicad address where notifications about
*                       communication errors will be sent.
*
* @return     GLO_TRUE  In case client was successfully registed.
*             GLO_FALSE In case of error while registering.
*
* @par Description:
* The AaSysComRegisterForErrors function adds client to the communication
* error notification list. Clients on the list will receive notification after
* message delivery failure is detected and reported via
* \ref AaSysComReportCommError.
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
* AaSysComDeregisterForErrors, AaSysComReportCommError
*
* @par Example:
*
*   @code
*       TAaSysComSicad client = AaSysComSicadGet(TEST_CPID, TEST_NID);
*
*       if(AaSysComRegisterForErrors(client) == GLO_FALSE)
*       {
*           // failed to register client
*       }
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComRegisterForErrors(const TAaSysComSicad client);

/**
********************************************************************************
*
* @brief      Deregisters client from communication error notifications.
*
* @param[in]  client    Specifies sicad address of client to be deregistered.
*
* @return     GLO_TRUE  In case client was successfully deregistered.
*             GLO_FALSE In case of error while deregistering.
*
* @par Description:
* The AaSysComDeregisterForErrors function removes client from communication
* error notification list.
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
* AaSysComRegisterForErrors, AaSysComReportCommError
*
* @par Example:
*
*   @code
*       TAaSysComSicad client = AaSysComSicadGet(TEST_CPID, TEST_NID);
*
*       if(AaSysComDeregisterForErrors(client) == GLO_FALSE)
*       {
*           // failed to deregister client
*       }
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComDeregisterForErrors(const TAaSysComSicad client);

/**
********************************************************************************
*
* @brief          Reports communication error.
*
* @param[in]      reporter      Error reporter's cpid.
*
* @param[in]      errorType     Specifies type of communication error.
*
* @param[in,out]  message       Points to a pointer to the handle of the message.
*                               It is nulled by return.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComReportCommError function reports communication error which will
* be forwarded to clients on communication error notification list.
* Ownership of the message is transferred and releasing the message and related
* resources is handled by the function. Note that those resources are not
* released in DSP environment!
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* In case delivery of communication failure notification message fails, no
* notification will be sent to registered clients (this is endless looping
* prevention).
* \n In case \p message is \c GLO_NULL or \p *message is \c GLO_NULL
* function does no action.
*
* @par Usage:
* Reporting communications errors is enabled by default. Error reporting can be
* disabled via RAD tag ERadCcs_AaSysComCommErrNotifyDisabled.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComRegisterForErrors, AaSysComDeregisterForErrors
*
* @par Example:
*
*   @code
*       TAaSysComCpid ownCpid = 0;
*       ownCpid = AaSysComUserRegister(TEST_CPID, AaProEuCurrent());
*
*       // communication error detected
*
*       AaSysComReportCommError(ownCpid,
*                               ERROR_TYPE,
*                               &msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComReportCommError(const TAaSysComCpid reporter,
                             const u32 errorType,
                             void **message);

/**
********************************************************************************
*
* @brief      Get own node id of the requesting user.
*
* @return     The function returns the SIC node identifier (NID), if successful.
*             Otherwise and in case the node identifier is not set yet, it
*             returns AASYSCOM_NODE_INVALID.
*
* @par Description:
* The AaSysComGetOwnNid function gets the node id of the requesting user.
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
*       TAaSysComNid ownNid = 0;
*       ...
*       ownNid = AaSysComGetOwnNid();
*   @endcode
*
*******************************************************************************/
TAaSysComNid AaSysComGetOwnNid(void);


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
*   @param[in]  sizeOfEuArg   Size of the argument (in bytes) to forward to
*                             EU.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*
*   This function creates and starts a priorized execution unit.
*   It uses the AaPro function AaProEuCreateAndStart to create a Posix thread.
*   Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
*   (layering of AaSysCom and AaPro).
*
*   Internally a SysCom message queue will automatically be created and attached to the new thread.
*   Furthermore this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
*
*   Changes in \p euArgPtr causes no effect to the created Eu after creation, because
*   AaProEuCreateAndStart function copy \p euArgPtr.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - EAaProEuRetVal_OutOfResources if maximum number of EUs would be
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
*   #include <IfAaSysCom.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaSysComEuCreateAndStart(
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
*   Macro AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
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
AaSysComEuCreateAndStart(u32*                euIdPtr,
                         const char          *euNamePtr,
                         TAaProEuEntryPoint  *euEntryPoint,
                         u32                  euStackSize,
                         u32                  euPriority,
                         void*                euArgPtr,
                         u32                  sizeOfEuArg);


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
*   @param[in]  sizeOfEuArg   Size of the argument (in bytes) to forward to EU.
*   @param[in]  join          Defines if EU is joinable or not.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*   This function creates and starts a priorized execution unit as a real-time or background process.
*   It uses the AaPro function AaProEuCreateAndStartWithPolicy to create a Posix thread.
*   Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
*   (layering of AaSysCom and AaPro).
*
*   Internally a SysCom message queue will automatically be created and attached to the new thread.
*   Furthermore this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
*
*   Changes in \p euArgPtr causes no effect to the created Eu after creation, because
*   AaProEuCreateAndStart function copy \p euArgPtr.
*
*   In case (sizeOfEuArg == 0):
*   Modification of the memory where \p euArgPtr is pointing to does have effect to the created
*   EU after creation, because AaProEuCreateAndStart function passes the \p euArgPtr
*   directly to the pthread. The user is responsible for freeing the memory to
*   which \p euArgPtr refers.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - EAaProEuRetVal_OutOfResources if maximum number of EUs would be
*        exceeded
*
*   @par Restrictions:
*   This function is used on Linux target only.
*
*   @par Example:
*   Following example shows how to create and start execution unit
*
*   @code
*   // example 1 - with argument copy (sizeOfEuArg > 0)
*
*   #include <IfAaPro.h>
*   #include <IfAaSysCom.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaSysComEuCreateAndStartWithPolicy(
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
*   // example 2 - no argument copy (sizeOfEuArg == 0)
*
*   #include <IfAaPro.h>
*   #include <IfAaSysCom.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaSysComEuCreateAndStartWithPolicy(
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
*   Macro AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
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
AaSysComEuCreateAndStartWithPolicy(u32*                     euIdPtr,
                                   const char               *euNamePtr,
                                   TAaProEuEntryPoint       *euEntryPoint,
                                   u32                      euStackSize,
                                   EAaProEuSchedulingPolicy euPolicy,
                                   u32                      euPriority,
                                   i32                      euNiceness,
                                   void*                    euArgPtr,
                                   u32                      sizeOfEuArg,
                                   TBoolean                 join);


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
*   @param[in]  euOsPoolId    Not used.
*   @param[in]  euPriority    The priority level for the EU.
*   @param[in]  euArgPtr      Pointer to the argument forwarded to new EU.
*   @param[in]  sizeOfEuArg   Size of the argument (in bytes) to forward to
*                             EU.
*
*   @return EAaProEuRetVal_NoError
*   @return EAaProEuRetVal_Error
*   @return EAaProEuRetVal_InvalidValue
*   @return EAaProEuRetVal_OutOfResources
*
*   @par Description:
*
*   This function creates and starts a priorized execution unit.
*   <b>MCU specific:</b>As the pool parameter is not used anyway, it simply
*   calls AaProEuCreateAndStart to create a Posix thread.
*   Implementation is done due to LBT1701 to allow CC&S Refactoring on Linux
*   (layering of AaSysCom and AaPro).
*
*   \nInternally a SysCom message queue will automatically be created and attached to the new thread.
*   Furthermore this function subscribes to an AaPro ExitHandler to get rid of the message queue on thread exit.
*
*   Changes in \p euArgPtr causes no effect to the created Eu after creation, because
*   AaProEuCreateAndStart function copy \p euArgPtr.
*
*   @par Errors:
*   It depends on OS whether this function returns error code or OS itself
*   handles the error, if maximum number of concurrent EUs are exceeded.
*   \n
*   In case of failure following is returned:
*      - EAaProEuRetVal_Error if something failed when new Eu created.
*        E.g memory allocation failure
*      - EAaProEuRetVal_InvalidValue if some parameter values are invalid.
*      - EAaProEuRetVal_OutOfResources if maximum number of EUs would be
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
*   #include <IfAaSysCom.h>
*
*   TAaProEuEntryPoint exampleEuStart;
*
*   EAaProEuRetVal ret;
*   u32 euId;
*   char* param = "something";
*
*   ret = AaSysComEuCreateAndStartToPool(
*         &euId,
*         "exampleEu",       // EU name
*         exampleEuStart     // Start function
*         2048,              // Stack size
*         0,                 // Pool Id  !! NOT USED !!
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
*   Macro AAPRO_GET_EU_ARGS can be used to get pointer to the EU arguments
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
AaSysComEuCreateAndStartToPool(u32*         euIdPtr,
                         const char         *euNamePtr,
                         TAaProEuEntryPoint *euEntryPoint,
                         u32                euStackSize,
                         u16                euOsPoolId,
                         u32                euPriority,
                         void*              euArgPtr,
                         u32                sizeOfEuArg);

/**
 * @name Macros for handling EchoRouteReq
 *
 * Direct usage of this macros should be avoided. Function API should be used
 * instead.
 *
 * @{
 */

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlCalculateEchoRouteMsgLen
 *
 ******************************************************************************/
#define AASYSCOM_CALCULATE_ECHO_ROUTE_MSG_LEN(RECEIVERCOUNT, DATASIZE)  \
  AaSysComControlCalculateEchoRouteMsgLen((u16) RECEIVERCOUNT, (u32) DATASIZE);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSendEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SEND_ECHO_ROUTE_MSG(MSG, LINK)         \
  AaSysComControlSendEchoRouteReqMsg(MSG, LINK);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetReceiverCountToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_RECEIVER_COUNT_TO_ECHO_ROUTE_MSG(ROUTEREQ, RCOUNT) \
  AaSysComControlSetReceiverCountToEchoRouteReqMsg(ROUTEREQ, RCOUNT);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetSequenceNumberToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_SEQUENCE_NBR_TO_ECHO_ROUTE_MSG(ROUTEREQ, SEQ_NBR)  \
  AaSysComControlSetSequenceNumberToEchoRouteReqMsg(ROUTEREQ, SEQ_NBR);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetReceiverAddressToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_RECEIVER_ADDRESS_TO_ECHO_ROUTE_MSG(ROUTEREQ, N, SICADDR) \
  AaSysComControlSetReceiverAddressToEchoRouteReqMsg(ROUTEREQ, N, SICADDR);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_RECEIVER_TIMESTAMP_TO_ECHO_ROUTE_MSG(ROUTEREQ, N)  \
  AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg(ROUTEREQ, N);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetLinkForReceiverToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_LINK_FOR_RECEIVER_TO_ECHO_ROUTE_MSG(ROUTEREQ, N, LINK) \
  AaSysComControlSetLinkForReceiverToEchoRouteReqMsg(ROUTEREQ, N, LINK);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetEchoDataSizeToEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_SET_ECHODATASIZE_TO_ECHO_ROUTE_MSG(ROUTEREQ, ECHODATASIZE) \
  AaSysComControlSetEchoDataSizeToEchoRouteReqMsg(ROUTEREQ, ECHODATASIZE);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlSetEchoDataToEchoRouteReqMsg

 ******************************************************************************/
#define AASYSCOM_SET_ECHODATA_TO_ECHO_ROUTE_MSG(ROUTEREQ, ECHODATAPTR, ECHODATASIZE) \
  AaSysComControlSetEchoDataToEchoRouteReqMsg(ROUTEREQ, ECHODATAPTR, ECHODATASIZE);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_GET_ECHODATASIZE_FROM_ECHO_ROUTE_MSG(ROUTEREQ, ECHODATASIZEPTR) \
  AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg(ROUTEREQ, ECHODATASIZEPTR);

/**
 *******************************************************************************
 *
 *   @deprecated  instead of using this macro function below should be used
 *   @see         AaSysComControlGetEchoDataFromEchoRouteReqMsg
 *
 ******************************************************************************/
#define AASYSCOM_GET_ECHODATA_FROM_ECHO_ROUTE_MSG(ROUTEREQ, ECHODATAPTR, ECHODATASIZEPTR) \
  AaSysComControlGetEchoDataFromEchoRouteReqMsg(ROUTEREQ, ECHODATAPTR, ECHODATASIZEPTR);

/** @} */
/**
 * @name Macros
 *
 * @{
 */
/**
********************************************************************************
*
* @brief          Register the Event Machine user.
*
* @param[in]      userCpid  Specifies the communication point ID of the
*                           requesting user.
*
* @param[in]      qId       Specifies the event queue id of the requesting user.
*
* @param[in]      eventType Specifies the event type.
*
* @return         The function returns the communication point ID. If
*                 successful it is equal to the user-specified communication
*                 point ID. Otherwise it is zero.
*
* @deprecated     Use EmSysComRegister from Event Machine API
*
* @see
* AaSysComUserRegister
*
*******************************************************************************/
#define AaSysComEMUserRegister EmSysComRegister


/**
 * @brief Converts byte order of message envelope (header & trailer) fields
 *        from host to big endian.
 *
 * @param[in,out] message Pointer to message handle whose envelope will be
 *                converted.
 *
 * @return None
 *
 * @par Description:
 * AaSysComMsgEnvelopeHostToBigEndian converts byte order of messsge
 * envelope (header & trailer) fields from host to big endian. If the host is
 * big endian, this function is a no-op.
 *
 * @par Errors:
 * None
 *
 * @par Restrictions:
 * In case \p message is \c GLO_NULL function does no action.
 *
 * @par Usage:
 * This function is used by SysCom internally when routing message out from a
 * node.
 *
 * @par Rationale:
 * None
 *
 * @par Future directions:
 * None
 *
 * @see AaSysComMsgEnvelopeBigEndianToHost
 *
 * @par Example:
 *   @code
 *   None
 *   @endcode
 */
#if defined(CCS_LITTLE_ENDIAN) /* change order if in little endian machine */
void AaSysComMsgEnvelopeHostToBigEndian(const void *message);
#elif defined (CCS_BIG_ENDIAN)
#define AaSysComMsgEnvelopeHostToBigEndian(A) (void)A
#else
#error "No endianness defined."
#endif


/**
 * @brief Converts byte order of message envelope (header & trailer) fields
 *        from host to big endian.
 *
 * @param[in,out] message Pointer to message handle whose envelope will be
 *                converted.
 *
 * @return None
 *
 * @par Description:
 * AaSysComMsgEnvelopeHostToBigEndian converts byte order of messsge
 * envelope (header & trailer) fields from host to big endian. If the host is
 * big endian, this function is a no-op.
 *
 * @par Errors:
 * None
 *
 * @par Restrictions:
 * In case \p message is \c GLO_NULL function does no action.
 *
 * @par Usage:
 * This function is used by SysCom internally when routing message out from a
 * node.
 *
 * @par Rationale:
 * None
 *
 * @par Future directions:
 * None
 *
 * @see AaSysComMsgEnvelopeBigEndianToHost
 *
 * @par Example:
 *   @code
 *   None
 *   @endcode
 */
#if defined(CCS_LITTLE_ENDIAN) /* change order if in little endian machine */
void AaSysComMsgEnvelopeBigEndianToHost(const void *message);
#elif defined (CCS_BIG_ENDIAN)
#define AaSysComMsgEnvelopeBigEndianToHost(A) (void)A
#else
#error "No endianness defined."
#endif

/**
 * @brief  Sets payload of a word-oriented message to big endian byte order
 *         from host.
 *
 * @param[in,out] message Pointer to message handle in whose message payload
 *                must be converted.
 *
 * @return None
 *
 * @par Description:
 * AaSysComWordOrientedMsgToBig converts byte order of word-oriented message
 * payload to BIG endian format.
 * If already in BIG endian nothing is done.
 * This function can be used by application if there is need to convert the
 * message payload to Big endian (network endian) format.
 * The function also updates the Message Application Part Format (MAPF) flags
 * accordingly.
 * The function checks if length of the message is divisible by 4 - it must be
 * because this function is supposed to be used with word-oriented messages.
 * If length not divisible by 4 error is written to log. The message can not be
 * destroyed since the information of destroying the message can not be provided
 * to application (with current PrepareSend_ (marshalling) function interface
 * having 'void *message'). On the other hand in case the interface would be
 * 'void **message' and if message would be destroyed and pointer nulled by
 * PrepareSend_ (marshaling) function, could we trust that application every
 * time checks if message was destroyed. Dealing with NULL pointer would cause
 * SW to fall with no error message in UDP log yet (post mortem log should
 * contain the log, but it might not be so easily found).
 *
 * @par Errors:
 * None
 *
 * @par Restrictions:
 * In case \p message is \c GLO_NULL function does no action.
 *
 * @par Usage:
 * None
 *
 * @par Rationale:
 * None
 *
 * @par Future directions:
 * None
 *
 * @see AaSysComWordOrientedMsgToHost
 *
 * @par Example:
 *   @code
 *   None
 *   @endcode
 */
#if defined(CCS_LITTLE_ENDIAN) /* change order if in little endian machine */
void AaSysComWordOrientedMsgToBig(const void *message);
#elif defined (CCS_BIG_ENDIAN)
#define AaSysComWordOrientedMsgToBig(A) (void)A
#else
#error "No endianness defined."
#endif


/* The following macros are meant to be used by application SW to be able to
 * carry u64 fields split to two parts in word-oriented message. Application
 * is responsible of defining the message structure having one u64 in two u32
 * parts, setting the u64 variable to 'u32 pieces' to message in sending end
 * and combining the 'u32 pieces' to u64 variable in receiving end.
 */

/**
 * @brief Extracts the 32 most significant bits from an u64.
 *
 * @param[in] u64Var u64 variable to be split to u32 pieces.
 *
 * @par Description:
 * The AaSysComMSWof64 macro extracts the 32 most significant bits of
 * \p u64Var and returns the result as an unsigned 32-bit integer (u32).
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
 * @see None
 *
 * @par Example:
 */
#define AaSysComMSWof64(u64Var)        CCS_STATIC_CAST(u32,(u64Var >> 32))

/**
 * @brief Extracts the 32 lest significant bits from an u64.
 *
 * @param[in] u64Var u64 variable to be split to u32 pieces.
 *
 * @par Description:
 * The AaSysComLSWof64 macro extracts the 32 least significant bits of
 * \p u64Var and returns the result as an unsigned 32-bit integer (u32).
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
 * @see None
 *
 * @par Example:
 */
#define AaSysComLSWof64(u64Var)        CCS_STATIC_CAST(u32,u64Var)

/**
********************************************************************************
*
* @brief      Macros to split and combine u64 field in word oriented message.
*
* @param[in] MSW        Most significant part of u64 to be combined. The
*                       parameter is used by AaSysComExtend32To64
*
* @param[in] LSW        Least significant part of u64 to be combined. The
*                       parameter is used by AaSysComExtend32To64
*
* @par Description:
* AaSysComExtend32To64 combines MS and LS parts to a u64 variable.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* None.
*
* @par Usage:
* NOTE that SysCom swaps the contents of the word-oriented message including
* the u32 pieces of the u64Var. This means that the apllication must not
* perform any swapping.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* None
*
* @par Example:
*
*******************************************************************************/
#define AaSysComExtend32To64(MSW, LSW) (((CCS_STATIC_CAST(u64,MSW)) << 32) | (CCS_STATIC_CAST(u64,LSW)))


/**
********************************************************************************
*
* @brief      Gets the endianness of the host
*
* @par Description:
* The AaSysComGetHostEndianness macro 'returns' the endianness of the host.
* The "returned" value is of type EAaSysComEndianness defined together with
* this macro.
* The macro uses compilation switches CCS_BIG_ENDIAN and CCS_LITTLE_ENDIAN
* to define the "returned" value. Thus no code is generated.
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
* None
*
* @par Example:
*   @code
*       if (EAaSysComEndianness_Little == AaSysComGetHostEndianness())
*       {
*         // we are in Little endian machine  - do something
*         ...
*       }
*   @endcode
*
*******************************************************************************/
#if defined (CCS_LITTLE_ENDIAN)
#define AaSysComGetHostEndianness() EAaSysComEndianness_Little
#elif defined(CCS_BIG_ENDIAN)
#define AaSysComGetHostEndianness() EAaSysComEndianness_Big
#else
#define AaSysComGetHostEndianness() EAaSysComEndianness_NotDefined
// Is it always error case ?
#error "No endianness defined !"
#endif


/* @} */





/** @} end: @addtogroup dgAaSysComCommon AaSysCom Common */


#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOM_H */
