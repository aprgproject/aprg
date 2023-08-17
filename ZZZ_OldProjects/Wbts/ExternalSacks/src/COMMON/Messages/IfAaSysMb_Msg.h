/** @file
* @brief AaSysMb common messages
* @copyright 2016 Nokia Solutions and Networks. All rights reserved.
* @copyright 2019 Nokia. All rights reserved.
*/

#ifndef COMMON_IFAASYSMB_MSG_H
#define COMMON_IFAASYSMB_MSG_H

#include <glo_def.h>
#include <IfAaSysCom.h>
#include <CcsCommon.h>
#include <IfAaSysMb_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysMbMsg AaSysMb common messages
 * @ingroup dgAaSysMb
 */
/*@{*/

/** @name Message Broker related message ids. Can be used as message API.
 * @{
 */
#define AASYSMB_PUBL_CMD_MSG        0x08A6      /* !- SIGNO(struct SAaSysMbPublCmdMsg) -! */
#define AASYSMB_PUBL_REPLY_MSG      0x0BA7      /* !- SIGNO(struct SAaSysMbPublReplyMsg) -! */
#define AASYSMB_UNPUBL_CMD_MSG      0x08CE      /* !- SIGNO(struct SAaSysMbUnpublCmdMsg) -! */
#define AASYSMB_UNPUBL_REPLY_MSG    0x0BA8      /* !- SIGNO(struct SAaSysMbUnpublReplyMsg) -! */
#define AASYSMB_SUBS_CMD_MSG        0x08A5      /* !- SIGNO(struct SAaSysMbSubsCmdMsg) -! */
#define AASYSMB_SUBS_REPLY_MSG      0x0BA9      /* !- SIGNO(struct SAaSysMbSubsReplyMsg) -! */
#define AASYSMB_UNSUBS_CMD_MSG      0x08CB      /* !- SIGNO(struct SAaSysMbUnsubsCmdMsg) -! */
#define AASYSMB_UNSUBS_REPLY_MSG    0x0BAA      /* !- SIGNO(struct SAaSysMbUnsubsReplyMsg) -! */
#define AASYSMB_FLUSH_CMD_MSG       0x084E      /* !- SIGNO(struct SAaSysMbFlushCmdMsg) -! */
#define AASYSMB_FLUSH_REPLY_MSG     0x0BAB      /* !- SIGNO(struct SAaSysMbFlushReplyMsg) -! */
/**
 * @}
 */

#define AASYSMB_GLOBAL_NODE_LIST_MSG    0x0C5E  /* !- SIGNO(struct SAaSysMbGlobalNodeListMsg) -! */


/** @brief Structure containing parameters for Message Broker. */
typedef struct SAaSysMbMsg
{
    u32 agent;                          /**< Who sent the message */
    u32 operation;                      /**< What is to be done? subscribe, update records? */
    u32 channel;                        /**< Channel on which the operation is done */
    TAaSysMbZoneId zone;                /**< Zone on which the operation is done */
    TAaSysComSicad sicad;               /**< Sicad of the operation object (publisher, subscriber etc) */
#ifndef CCS_LITTLE_ENDIAN
    TAaSysComMsgSize size;              /**< Size of the published message payload (0 if no payload) */
    TAaSysComMsgId msgId;               /**< Message id of the message to publish or subscribe */
#else
    TAaSysComMsgId msgId;               /**< Message id of the message to publish or subscribe */
    TAaSysComMsgSize size;              /**< Size of the published message payload (0 if no payload) */
#endif
    u32 reserved;                       /**< Reserved for Message Broker internal usage. */
} SAaSysMbMsg;



/**
********************************************************************************
* @brief Message Broker message structure used for message publish.
*
* @see  AaSysMbPrepare, AaSysMbPublish
*******************************************************************************/
typedef struct SAaSysMbPublCmdMsg
{
    SAaSysMbMsg msgParams;  /**< Parameters for message publish. */
    u8 publishedMsg[4];     /**< Payload of the message to be published. */
} SAaSysMbPublCmdMsg;

/**
********************************************************************************
* @brief Message Broker message structure passed to the application containing
*        result of message publication.
*
* @see  AaSysMbPrepare, AaSysMbPublish
*******************************************************************************/
typedef struct SAaSysMbPublReplyMsg
{
    SAaSysMbMsg msgParams;  /**< Parameter copied from SAaSysMbPublCmdMsg */
                            /**< message to help identify response. */
    u32 status;             /**< Status of the operation. */
} SAaSysMbPublReplyMsg;


/**
********************************************************************************
* @brief Message Broker message structure used for message unpublish.
*
* @see  AaSysMbUnpublish
*******************************************************************************/
typedef struct SAaSysMbUnpublCmdMsg
{
    SAaSysMbMsg msgParams;  /**< Parameters for message unpublish. */
} SAaSysMbUnpublCmdMsg;

/**
********************************************************************************
* @brief Message Broker message structure passed to the application containing
*        result of message unpublish.
*
* @see  AaSysMbUnpublish
*******************************************************************************/
typedef struct SAaSysMbUnpublReplyMsg
{
    SAaSysMbMsg msgParams;  /**< Parameter copied from SAaSysMbUnpublCmdMsg */
                            /**< message to help identify response. */
    u32 status;             /**< Status of the operation. */
} SAaSysMbUnpublReplyMsg;


/**
********************************************************************************
* @brief Message Broker message structure used for message subcribe.
*
* @see  AaSysMbSubscribe
*******************************************************************************/
typedef struct SAaSysMbSubsCmdMsg
{
    SAaSysMbMsg msgParams;  /**< Parameters for message subscribe. */
} SAaSysMbSubsCmdMsg;

/**
********************************************************************************
* @brief Message Broker message structure passed to the application containing
*        result of message subscribe.
*
* @see  AaSysMbSubscribe
*******************************************************************************/
typedef struct SAaSysMbSubsReplyMsg
{
    SAaSysMbMsg msgParams;  /**< Parameter copied from SAaSysMbSubsCmdMsg */
                            /**< message to help identify response. */
    u32 status;             /**< Status of the operation. */
} SAaSysMbSubsReplyMsg;


/**
********************************************************************************
* @brief Message Broker message structure used for message unsubcribe.
*
* @see  AaSysMbUnsubscribe
*******************************************************************************/
typedef struct SAaSysMbUnsubsCmdMsg
{
    SAaSysMbMsg msgParams;  /**< Parameters for message unsubscribe. */
} SAaSysMbUnsubsCmdMsg;

/**
********************************************************************************
* @brief Message Broker message structure passed to the application containing
*        result of message unsubscribe.
*
* @see  AaSysMbUnsubscribe
*******************************************************************************/
typedef struct SAaSysMbUnsubsReplyMsg
{
    SAaSysMbMsg msgParams;  /**< Parameter copied from SAaSysMbUnsubsCmdMsg */
                            /**< message to help identify response. */
    u32 status;             /**< Status of the operation. */
} SAaSysMbUnsubsReplyMsg;


/**
********************************************************************************
* @brief Message Broker message structure used for message flush.
*
* @see  AaSysMbFlush
*******************************************************************************/
typedef struct SAaSysMbFlushCmdMsg
{
    SAaSysMbMsg msgParams;  /**< Parameters for message flush. */
} SAaSysMbFlushCmdMsg;

/**
********************************************************************************
* @brief Message Broker message structure passed to the application containing
*        result of message flush.
*
* @see  AaSysMbFlush
*******************************************************************************/
typedef struct SAaSysMbFlushReplyMsg
{
    SAaSysMbMsg msgParams;  /**< Parameter copied from SAaSysMbFlushCmdMsg */
                            /**< message to help identify response. */
    u32 status;             /**< Status of the operation. */
} SAaSysMbFlushReplyMsg;


/**
********************************************************************************
* @brief List of nodes registered to AaSysMbServer. This message is published
*        each time node is added or removed from AaSysMbServer global node list.
*******************************************************************************/
typedef struct SAaSysMbGlobalNodeListMsg
{
    u32 nodeCount;          /**< Number of nodes in list. */
    u32 nodeId[1];          /**< Dynamic array of nodes. */
} SAaSysMbGlobalNodeListMsg;

/**@}*/


#ifdef __cplusplus
}
#endif


#endif /* COMMON_IFAASYSMB_MSG_H */
