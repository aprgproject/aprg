/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef IF_MCU_AASYSCOM_H
#define IF_MCU_AASYSCOM_H
#include <CcsCommon.h>
#include <glo_def.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../../COMMON/ServiceInterface/IfAaSysCom.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaSysCom.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaSysCom_Defs.h"
#include "../../SHARED/MCU_RT/Messages/IfAaSysCom_Msg.h"
#endif


/* Include the inline implementation if needed. */
#ifdef AASYSCOM_USE_INLINE_IMPL
# include "IfAaSysCom_inline.h"
#endif /* AASYSCOM_USE_INLINE_IMPL */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComMcu AaSysCom MCU
 * @ingroup dgAaSysCom
 * @{
 */


/**
********************************************************************************
*
* @brief      Enables large messages processing on execution environment (application) level.
*
* @par Description:
* Each application that wants to process large messages must first enable large message support
* by calling either AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport()
* Otherwise each attempt to create a large message is failed and logged as error and messages
* sent to CPIDs owned by such execution units are dropped with respective warning in message
* receive API functions.<br>
* AaSysComEeEnableLargeMessageSupport() enables the large message API for all current and future
* execution units of the calling execution environment. Further calling AaSysComEuEnableLargeMessageSupport()
* is allowed yet redundant and yields no error.
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
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComEuEnableLargeMessageSupport, AaSysComMsgIsLarge, AaSysComLargeMsgCreate,
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE
*
*
*******************************************************************************/
void AaSysComEeEnableLargeMessageSupport(void);

/**
********************************************************************************
*
* @brief      Enables large messages processing on execution unit (thread) level.
*
* @par Description:
* Each application that wants to process large messages must first enable large message support
* by calling either AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport()
* Otherwise each attempt to create a large message is failed and logged as error and messages
* sent to CPIDs owned by such execution units are dropped with respective warning in message
* receive API functions.<br>
* AaSysComEuEnableLargeMessageSupport() enables the large message API for the calling execution
* unit only. Further calling AaSysComEeEnableLargeMessageSupport() is allowed and yields no error.
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
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComEeEnableLargeMessageSupport, AaSysComMsgIsLarge, AaSysComLargeMsgCreate,
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE
*
*
*******************************************************************************/
void AaSysComEuEnableLargeMessageSupport(void);

/**
********************************************************************************
*
* @brief      Returns maximum possible size of large message.
*
* @return     Maximum allowed payload size in bytes.
*
* @par Description:
* Returns maximum possible size of large message that can be created or
* received from another node.
*
* @par Errors:
* 0 is returned in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_MAXSIZE, AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE,
* AaSysComEeEnableLargeMessageSupport,
* AaSysComMsgGetMaxPayload, AaSysComLargeMsgCreate
*
*
*******************************************************************************/
TAaSysComLargeMsgSize AaSysComMsgGetMaxLargePayload(void);

/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a large message.
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
*               <tt>GLO_NULL</tt> is returned.
*
* @par Description:
* The AaSysComLargeMsgCreate() function reserves and prepares appropriate resources
* for the large message. Large messages are created in separate message pool designed specifically
* for messages of payload size exceeding maximum value defined by SIC specification.
* <br>
* AaTrace has partially support for tracing large messages. When tracing in normal mode (to SIC/TCP)
* AaTrace will trace only 65418 bytes of original message payload.
* When using tracing to AaSysLog (can be enabled via RAD flags) whole message will be dumped to log.
* Also when tracing to AaSysLog additional SysCom header is added between standard SysCom header and payload.
*
* @par Errors:
* The function returns <tt>GLO_NULL</tt> in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value,
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport(),
* \li there is no enough free space in the pool for large messages,
* \li <tt>messagePayloadSize</tt> exceeds the value returned from AaSysComMsgGetMaxLargePayload().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_MAXSIZE, AaSysComEeEnableLargeMessageSupport,
* AaSysComLargeMsgCreateReply, AaSysComLargeMsgCreateCopy,
* AaSysComLargeMsgCreateCopyRe, AaSysComLargeMsgCreateCopyTo,
* AaSysComMsgDestroy, AaSysComMsgSend
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComLargeMsgSize msgPayloadSize = 1048576;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComLargeMsgCreate(msgId, msgPayloadSize, msgTarget);
*   @endcode
*
*******************************************************************************/
void *AaSysComLargeMsgCreate(const TAaSysComMsgId messageId,
                             const TAaSysComLargeMsgSize messagePayloadSize,
                             const TAaSysComSicad messageTarget);

/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a large reply message.
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
* The AaSysComLargeMsgCreateReply() function reserves and prepares resources for
* the reply message, sender and receiver addresses of which are taken from the
* original message by swapping those. The original message can be both standard or
* large one.
*
* @par Errors:
* The function returns <tt>GLO_NULL</tt> in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value,
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport(),
* \li there is no enough free space in the pool for large messages,
* \li <tt>messagePayloadSize</tt> exceeds the value returned from AaSysComMsgGetMaxLargePayload().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComEeEnableLargeMessageSupport, AaSysComLargeMsgCreate
*
* @par Example:
*   @code
*       void *replyMsgPtr = GLO_NULL;
*       void *originalMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComLargeMsgSize msgPayloadSize = 1048576;
*       ...
*       originalMsgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       replyMsgPtr = AaSysComLargeMsgCreateReply(msgId, msgPayloadSize, originalMsgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComLargeMsgCreateReply(const TAaSysComMsgId messageId,
                                  const TAaSysComLargeMsgSize messagePayloadSize,
                                  const void *repliedMessage);

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
* The AaSysComLargeMsgCreateCopy() function reserves and prepares resources for the
* large message and fills it with a copy of the original message. The original message can
* be both standard or large one.
*
* @par Errors:
* The function returns <tt>GLO_NULL</tt> in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value,
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport(),
* \li there is no enough free space in the pool for large messages,
* \li <tt>messagePayloadSize</tt> exceeds the value returned from AaSysComMsgGetMaxLargePayload().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComEeEnableLargeMessageSupport, AaSysComLargeMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *copyMsgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       copyMsgPtr = AaSysComLargeMsgCreateCopy(msgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComLargeMsgCreateCopy(const void *originalMessage);

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
* The AaSysComLargeMsgCreateCopyRe() function reserves and prepares resources for
* the large reply message and fills it with a copy of the original message. The
* receiver of the message is the sender of the user-specified replied message.
* The original and replied messages can be both standard or large ones.
*
* @par Errors:
* The function returns <tt>GLO_NULL</tt> in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value,
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport(),
* \li there is no enough free space in the pool for large messages,
* \li <tt>messagePayloadSize</tt> exceeds the value returned from AaSysComMsgGetMaxLargePayload().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see AaSysComEeEnableLargeMessageSupport, AaSysComLargeMsgCreateCopy
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *origMsgPtr = GLO_NULL;
*       void *repliedMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComLargeMsgSize msgPayloadSize = 1048576;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       origMsgPtr = AaSysComLargeMsgCreate(msgId, msgPayloadSize, msgTarget);
*       repliedMsgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       msgPtr = AaSysComLargeMsgCreateCopyRe(origMsgPtr, repliedMsgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComLargeMsgCreateCopyRe(const void *originalMessage,
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
* The AaSysComLargeMsgCreateCopyTo() function reserves and prepares resources for
* the message and fills it with a copy of the original message into the
* message. The receiver of the message is the user-specified target.
*
* @par Errors:
* The function returns <tt>GLO_NULL</tt> in any of the following cases:
* \li \ref AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size" is not set to a non-zero value,
* \li large message support hasn't been enabled by calling AaSysComEeEnableLargeMessageSupport() or AaSysComEuEnableLargeMessageSupport(),
* \li there is no enough free space in the pool for large messages,
* \li <tt>messagePayloadSize</tt> exceeds the value returned from AaSysComMsgGetMaxLargePayload().
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComEeEnableLargeMessageSupport, AaSysComLargeMsgCreate
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       void *origMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComLargeMsgSize msgPayloadSize = 1048576;
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID_1, TEST_NID);
*       TAaSysComSicad newTarget = AaSysComSicadGet(TEST_CPID_2, TEST_NID);
*       ...
*       origMsgPtr = AaSysComLargeMsgCreate(msgId, msgPayloadSize, msgTarget);
*       msgPtr = AaSysComLargeMsgCreateCopyTo(origMsgPtr, newTarget);
*   @endcode
*
*******************************************************************************/
void *AaSysComLargeMsgCreateCopyTo(const void *originalMessage,
                              const TAaSysComSicad messageTarget);

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
* The AaSysComMsgGetPayloadSizeExt() function reveals the size of the message
* application part (user payload) of the user-specified message. For standard messages
* returned value is in range from 0 to the value returned from AaSysComMsgGetMaxPayload().
* For large messages returned value is in range from 0 to the value returned from
* AaSysComMsgGetMaxLargePayload().
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
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_MAXSIZE, AaSysComLargeMsgCreate,
* AaSysComMsgReceive, AaSysComMsgGetPayloadSize, AaSysComMsgIsLarge
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComLargeMsgSize payloadSize = 0;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       payloadSize = AaSysComMsgGetPayloadSizeExt(msgPtr);
*   @endcode
*
*******************************************************************************/
TAaSysComLargeMsgSize AaSysComMsgGetPayloadSizeExt(const void *message);

/**
********************************************************************************
*
* @brief      Reveal message type (standard or large)
*
* @param[in]  message       Points to the handle of the message.
*
* @return     The function returns GLO_TRUE if the message is a large one and GLO_FALSE otherwise.
*
* @par Description:
* The AaSysComMsgIsLarge() function reveals message type of the user-specified message.
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
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgCreate, AaSysComLargeMsgCreate, AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE,
* AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_MAXSIZE
*
* @par Example:
*   @code
*       void *msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       void *copyPtr = GLO_NULL;
*       if (GLO_TRUE == AaSysComMsgIsLarge())
          copyPtr = AaSysComLargeMsgCreateCopy(msgPtr);
        else
          copyPtr = AaSysComMsgCreateCopy(msgPtr)
*       ...
*       AaSysComMsgSend(copyPtr);
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComMsgIsLarge(const void *message);

/**
********************************************************************************
*
* @brief    Get IPC large message pool usage.
*
* @return   The function returns large message pool usage (in percent).
*
* @par Description:
* The AaSysComGetIpcLargeMessagePoolUsage() function returns usage of the pool for large messages.
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
* LBT2950.
*
* @par Future directions:
* None.
*
* @see
* AaSysComLargeMsgCreate, AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE
*
* @par Example:
*   @code
*       u32 messagePoolUsage = 0;
*
*       messagePoolUsage = AaSysComGetIpcLargeMessagePoolUsage();
*   @endcode
*
*******************************************************************************/
u32 AaSysComGetIpcLargeMessagePoolUsage(void);

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
* The AaSysComMsgCreateInitialized() function reserves and prepares appropriate
* resources for the message. Message body (user payload area) is wiped out
* (set to zero).
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
*       msgPtr = AaSysComMsgCreateInitialized(msgId, msgPayloadSize, msgTarget);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateInitialized(const TAaSysComMsgId messageId,
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
* The AaSysComMsgCreateInitializedReply() function reserves and prepares
* resources for the reply message, sender and receiver addresses of which
* are taken from the original message by swapping those. Message body
* (user payload area) is wiped out (set to zero).
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
* AaSysComMsgCreateInitialized
*
* @par Example:
*   @code
*       void *replyMsgPtr = GLO_NULL;
*       void *originalMsgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = (TAaSysComMsgSize)sizeof(TestMessage);
*       ...
*       originalMsgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       replyMsgPtr = AaSysComMsgCreateInitializedReply(msgId, msgPayloadSize,
*                                                       originalMsgPtr);
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateInitializedReply(const TAaSysComMsgId messageId,
                                        const TAaSysComMsgSize messagePayloadSize,
                                        const void *repliedMessage);

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
* The AaSysComMsgCreateX() function reserves and prepares resources for the
* message to be sent over the user-specified route using the user-specified
* transfer mode. Message body (user payload area) is wiped out (set to zero).
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* AaSysComMsgCreateInitializedX function must be used together with
* AaSysComMsgSendViaLink function.
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
* AaSysComMsgCreateInitialized, AaSysComMsgSendViaLink
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       TAaSysComLinkId linkId = AASYSCOM_LINK_SRIO;
*       ...
*       msgPtr = AaSysComMsgCreateInitializedX(myMsgId,
*                                              msgPayloadSize,
*                                              msgTarget,
*                                              EAaSysComMtm_Basic,
*                                              linkId);
*       if( GLO_NULL != msgPtr)
*       {
*           AaSysComMsgSendViaLink(&msgPtr,
*                                  EAaSysComSendPriority_Unspecified,
*                                  linkId);
*           ....
*       }
*   @endcode
*
*******************************************************************************/
void *AaSysComMsgCreateInitializedX(const TAaSysComMsgId messageId,
                                    const TAaSysComMsgSize messagePayloadSize,
                                    const TAaSysComSicad messageTarget,
                                    const EAaSysComMtm requestedTransferMode,
                                    const TAaSysComLinkId requestedLink);

/**
********************************************************************************
*
* @brief      Disable sending SysCom messages in EU context
*
* @param[in]  allow             boolean value to enable/disable sending in
*                               EU context
*
* @return     nothing
*
* @par Description:
* The AaSysComSendigInEuContext() function enables/disables possibility of
* sending SysCom messages in EU context. This option concern only messages
* routed by AASYSCOM_SOCKET_LINK and is used only to internode communication.
* Intranode communication remains without changes.
* By default sending in EU context is enabled and can be changed by configuration
* tag AASYSCOM_CONFIG_TAG_SOCKETLINK_SEDING_IN_EU_CONTEXT on startup phase.
* Every application can change this in runtime by calling this function.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Concern only messages routed by AASYSCOM_SOCKET_LINK.
* This function is fully available only on FSMr3, FSMr4 where syscom sockets
* are supported by LFS.
*
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
* AASYSCOM_CONFIG_TAG_SOCKETLINK_SEDING_IN_EU_CONTEXT
*
* @par Example:
*   @code
*       TBoolean sendInEuContext = GLO_TRUE;
*       ...
*       AaSysComSendigInEuContext(sendInEuContext);
*   @endcode
*
*******************************************************************************/
void AaSysComSendigInEuContext(TBoolean allow);

/**
********************************************************************************
*
* @brief        Reset SF_MON flag in syscom message header.
*
* @param[in]    message           Pointer to the existing message.
*
* @par Description:
* The AaSysComMsgResetTraceFlag() function resets SF_MON message flag. The main
* purpose of this function is to allow message reuse - this way it can be
* traced again.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* Parameters:
* - \b MCU: In case \p message is \c GLO_NULL function does no action.
* - \b RT: Not supported.
* - \b DSP: Not supported.

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
*       void *msg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgResetTraceFlag(msg);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgResetTraceFlag(void *message);

/**
********************************************************************************
*
* @brief        Enable message caching in EU context
*
* @par Description:
* The AaSysComMsgEnableCachingEu() function enables message caching inside
* CCS internal IPC allocator for thread in which API was called.
*
* Behavior of AaSysComMsgDestroy() and AaSysComMsgCreate() API is slightly
* changed. When user calls AaSysComMsgDestroy() pointer to the message is
* stored in CCS internal structures.
*
* This way, when user calls AaSysComMsgCreate() next time, and message size
* argument is lower or equal than cached message size, pointer to new message
* is instantly returned, resulting in much faster message oriented operations,
* due to whole IPC message pool not being locked.
*
* At the moment when message is cached, its message id is set to
* AASYSCOM_CACHED_MSG. This way when message pool exhaustion fatality will
* happen, it will be possible to distinguish how many threads started caching
* message and if it is reason of such fatality. On thread termination, CCS MCU
* will destroy cached messages.
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
* AaSysCom
*
* @par Example:
*   @code
*        // Enable message caching inside thread that calls this API
*        AaSysComMsgEnableCachingEu();
*
*        void *msg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*
*        // Process message here (...)
*
*        // After next destroy, pointer to the message will be stored inside CCS.
*        AaSysComMsgDestroy(&msg);
*
*        const TAaSysComMsgId messageId = 0xBEEF;
*        const TAaSysComMsgSize messagePayloadSize = 800;
*        const TAaSysComSicad messageTarget = 0x10110601;
*        const TAaSysComSicad messageSender = 0x1011000C;
*
*        // If messagePayloadSize is lower or equal than cached message size, then
*        // creation of next syscom message will be instant due to caching.
*        msg = AaSysComMsgCreate(messageId, messagePayloadSize, messageTarget);
*
*        // Process message here (...)
*
*        if (msg)
*            AaSysComMsgSendS(&msg, messageSender);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgEnableCachingEu(void);

/**
********************************************************************************
*
* @brief      Set delivery order bit of the user-specified message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgSetDeliveryOrderBit() function sets delivery order bit of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: Used only on SRIO. In case \p message is \c GLO_NULL function logs warning and does no further action.
*
* @par Usage:
* SysCom message created by: \ref AaSysComMsgCreate, \ref AaSysComMsgCreateX, \ref AaSysComMsgCreateInitialized or
* \ref AaSysComMsgCreateInitializedX has delivery order bit turned off.
* The functions: \ref AaSysComMsgCreateReply, \ref AaSysComMsgCreateCopy, \ref AaSysComMsgCreateCopyRe, \ref AaSysComMsgCreateCopyTo
* and \ref AaSysComMsgCreateInitializedReply clear delivery order bit.
* Turn it on only if it is really necessary because it has big impact on performance level.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComMsgCreate, AaSysComMsgIsDeliveryOrderBitActive, AaSysComMsgClearDeliveryOrderBit
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       TAaSysComMsgId msgId = TEST_MSG;
*       TAaSysComMsgSize msgPayloadSize = sizeof(TestMessage);
*       TAaSysComSicad msgTarget = AaSysComSicadGet(TEST_CPID, TEST_NID);
*       ...
*       msgPtr = AaSysComMsgCreate(msgId, msgPayloadSize, msgTarget);
*       AaSysComMsgSetDeliveryOrderBit(msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgSetDeliveryOrderBit(void * const message);

/**
********************************************************************************
*
* @brief      Get delivery order bit of the user-specified message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns \c GLO_TRUE if delivery order bit is on or \c GLO_FALSE if it is off.
*
* @par Description:
* The AaSysComMsgIsDeliveryOrderBitActive() function returns delivery order bit of the
* user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: In case \p message is \c GLO_NULL function logs warning and returns \c GLO_FALSE.
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
* AaSysComMsgSetDeliveryOrderBit, AaSysComMsgClearDeliveryOrderBit
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       TBoolean orderBit = AaSysComMsgIsDeliveryOrderBitActive(msgPtr);
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComMsgIsDeliveryOrderBitActive(const void * const message);

/**
********************************************************************************
*
* @brief      Clear delivery order bit of the user-specified message.
*
* @param[in]  message  Points to the handle of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComMsgClearDeliveryOrderBit() function clears the delivery order bit of the user-specified message.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - \b MCU: Used only on SRIO. In case \p message is \c GLO_NULL function logs warning and does no action.
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
* AaSysComMsgSetDeliveryOrderBit, AaSysComMsgIsDeliveryOrderBitActive
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       AaSysComMsgClearDeliveryOrderBit(msgPtr);
*   @endcode
*
*******************************************************************************/
void AaSysComMsgClearDeliveryOrderBit(void * const message);

/**
********************************************************************************
*
* @brief        Get the list of messages from EU's message queue.
*
* @param[out]   msgInfo     Pointer to the list of message information.
* @param[in]    msgInfoSize The list size.
*
* @return       Success: Actual amount of messages stored in \p msgInfo.
*               Failure: -1
*
* @par Description:
* AaSysComMsgPoolGetMessages() fills the list of messages stored in EU's message queue.
* Starting from index 0 of \p msgInfo, messages are stored from the oldest to the newest.
* Only messages delivered to EU (not received) are filled.
* In case there are more messages than \p msgInfoSize, the amount specified by
* \p msgInfoSize will be filled in \p msgInfo.
* In case there are less messages than \p msgInfoSize, \p msgInfo will be filled
* with actual amount of messages.
* In case of failure, proper warning is printed and function returns -1.
*
* @par Errors:
* - in case \p msgInfo is \c GLO_NULL or \p msgInfoSize is 0,
* function prints proper warning and returns -1.
*
* @par Restrictions:
* - for large messages, IPC stores internal structure that points to
* large message. As result, \p msgSizeBytes will be the size of internal structure.

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
* SAaSysComMessageInfo, AaSysComGetPoolTotalSize, AaSysComGetPoolFreeSize
*
* @par Example:
*   @code
*       const u32 msgInfoSize = 10;
*       SAaSysComMessageInfo msgInfo[msgInfoSize] = {0};
*       i32 msgsAmount = AaSysComMsgPoolGetMessages(&msgInfo, msgInfoSize);
*       if (0 < msgsAmount)
*           // process pool information
*   @endcode
*
*******************************************************************************/
i32 AaSysComGetIpcMessages(SAaSysComMessageInfo *msgInfo, const u16 msgInfoSize);

/**
********************************************************************************
*
* @brief        Get the total size of the message pool in bytes.
*
* @return       Success: The total size of the message pool in bytes.
*               Failure: -1
*
* @par Description:
* AaSysComGetPoolTotalSize() return the total size of the message
* pool in bytes.
* In case of failure, proper warning is printed and function returns -1.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* None.

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
* AaSysComGetPoolFreeSize, AaSysComMsgPoolGetMessages
*
* @par Example:
*   @code
*       const i32 poolTotalSizeBytes = AaSysComGetPoolTotalSize();
*       if (0 <= poolTotalSizeBytes)
*           // process pool information
*   @endcode
*
*******************************************************************************/
i32 AaSysComGetIpcMessagePoolTotalSize(void);

/**
********************************************************************************
*
* @brief        Get the free size in the message pool in bytes.
*
* @return       Success: The free size in the message pool in bytes.
*               Failure: -1
*
* @par Description:
* AaSysComGetPoolFreeSize() return the free size in the message
* pool in bytes.
* In case of failure, proper warning is printed and function returns -1.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* None.

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
* AaSysComGetPoolTotalSize, AaSysComMsgPoolGetMessages
*
* @par Example:
*   @code
*       const i32 poolFreeSizeBytes = AaSysComGetPoolFreeSize();
*       if (0 <= poolFreeSizeBytes)
*           // process pool information
*   @endcode
*
*******************************************************************************/
i32 AaSysComGetIpcMessagePoolFreeSize(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOM_H */
