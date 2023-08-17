/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysMb common definitions
* @module                AaSysMb
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef COMMON_IFAASYSMB_DEFS_H
#define COMMON_IFAASYSMB_DEFS_H

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysMbDefs AaSysMb common definitions
 * @ingroup dgAaSysMb
 */
/*@{*/


/** @name Message Broker zone identifiers. Zones map to node level.
 * @{
 */
#define AASYSMB_ZONE_INVALID      0x0000  /**< Invalid/unspecified zone */
#define AASYSMB_ZONE_LOCAL_NODE   0x0001  /**< Local node only */
#define AASYSMB_ZONE_GLOBAL       0x000F  /**< All nodes in the system */
#define AASYSMB_ZONE_ANY          0x00FF  /**< Any zone */
/**
 * @}
 */


/** @name Message Broker operator. Defines who has sent the message.
 * @{
 */
#define AASYSMB_MESSAGE_API     0x0000F00F  /**< Define that indicates message API was used. */
/**
 * @}
 */

/** @name Static CP ids for Message Broker.
 * @{
 */
#define AASYSMB_SERVER_TASK     0x0602  /**< Static CP id for Message Broker Server task. */
/**
 * @}
 */


/** @name Configuration tags for informing Message Broker online status.
 * @{
 */
/** @brief Local Message Broker is online and local zone is available. */
#define AASYSMB_CONFIG_TAG_LOCAL_ONLINE  "sys.mw.broker.local.online"
/** @brief Message Broker Server is online and global zone is available. */
#define AASYSMB_CONFIG_TAG_SERVER_ONLINE "sys.mw.broker.server.online"
/**
 * @}
 */


/** @brief Sets time which local SysMb tries to connect to SysMb server.
 *  If server does not respond within this time, SysMb can only
 *  be used on local zone. Default time is 8 sec. */
#define AASYSMB_CONFIG_TAG_CONNECTTIME   "ccs.service.aasysmb.connecttime"


/** @brief Type for publication/subscription zone. */
typedef u32 TAaSysMbZoneId;


/** @brief Message broker flush mode */
typedef enum EAaSysMbFlushMode{
  EAaSysMbFlushMode_PublOnly  = 0,      /**< Only publications are deleted */
  EAaSysMbFlushMode_SubsOnly,           /**< Only subscriptions are deleted */
  EAaSysMbFlushMode_Both,               /**< Both publications and subscriptions are deleted */

  EAaSysMbFlushMode_NbrOf               /**< Not usable value. Keep this last. */
} EAaSysMbFlushMode;


/** @brief Message broker publish mode */
typedef enum EAaSysMbPublMode{

  EAaSysMbPublMode_Now = 0,     /**< Published message is forwarded to those subscribers who
                                     have subscribed such message.
                                     This mode of publication is used together with
                                     Subscribe new-mode subscriptions for basic one-to-many
                                     (publish/subscribe) communication. */
  EAaSysMbPublMode_KeepOne,     /**< Message is forwarded to its subscribers as in Now-mode.
                                     Message is also stored for further subscriptions.
                                     New publication of same Sic message id replaces older
                                     publication.
                                     Keep One-mode publications together with Subscribe
                                     all-mode subscriptions are usable for service discovery. */
  EAaSysMbPublMode_KeepMany,    /**< Message is forwarded to its subscribers as in Now-mode.
                                     Message is also stored for further subscriptions.
                                     New publication of same Sic message id and same publisher
                                     Sic address replaces older publication.
                                     This mode of publication can be used e.g. for SW bus
                                     replacement. */
  EAaSysMbPublMode_OneShot,     /**< Message is forwarded to its subscribers as in Now-mode.
                                     If no subscriptions exist, publication is stored for
                                     later subscriptions and after someone subscribes message,
                                     it is forwarded to subscriber and then deleted.
                                     OneShot-mode publications together with Subscribe OneShot-
                                     mode subscriptions can be used for unsynchronized token
                                     passing. */
  EAaSysMbPublMode_NbrOf        /**< Not usable value. Keep this last. */

} EAaSysMbPublMode;


/** @brief Message broker subscribe mode */
typedef enum EAaSysMbSubsMode{

  EAaSysMbSubsMode_All = 0,       /**< Matching keep-mode publications are forwarded to subscriber.
                                       Subscription is stored for further publications.
                                       This mode of subscription together with Keep One-mode
                                       publication is usable for service discovery. */
  EAaSysMbSubsMode_NewOnly,       /**< Subscription is stored for further publications.
                                       Subscription is valid until it is deleted.
                                       This mode of subscription is used together with Publish
                                       Now-mode publications for basic one-to-many
                                       (publish/subscribe) communication.*/
  EAaSysMbSubsMode_ExistingOnly,  /**< Matching keep-mode publications are forwarded to subscriber.
                                       Subscription is not stored. */
  EAaSysMbSubsMode_OneShot,       /**< Matching keep-mode publications are forwarded to subscriber.
                                       If no publications exist, subscription is stored and deleted
                                       after first matching publication.
                                       This mode subscription together with OneShot-mode
                                       publication can be used for unsynchronized token passing.*/
  EAaSysMbSubsMode_NbrOf          /**< Not usable value. Keep this last. */

} EAaSysMbSubsMode;


/** @brief Message broker return codes */
typedef enum EAaSysMbRetVal
{
    EAaSysMbRetVal_Ok = 0,              /**< No Error. */
    EAaSysMbRetVal_InvalidParam,        /**< Invalid parameter detected. */
    EAaSysMbRetVal_Error,               /**< Undefined error. */
    EAaSysMbRetVal_UnexpectedMessage,   /**< Unexpected message received. */
    EAaSysMbRetVal_MessageFailure,      /**< SIC-messaging failure. */
    EAaSysMbRetVal_UnsupportedZone,     /**< Message contains unsupported zone. */
    EAaSysMbRetVal_UnsupportedMode,     /**< Message contains unsupported mode. */
    EAaSysMbRetVal_InvalidSicad,        /**< Message contains unsupported sicad address. */
    EAaSysMbRetVal_InvalidNode,         /**< Message contains unsupported node. */
    EAaSysMbRetVal_InvalidPayloadSize,  /**< Message contains invalid payload size. */
    EAaSysMbRetVal_NotInitialized,      /**< Message Broker not initialized. */

    EAaSysMbRetVal_UndefinedError       /**< Undefined error, should not happen. Meaningful return-code should be available.
                                             Keep this last.*/
} EAaSysMbRetVal;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* COMMON_IFAASYSMB_DEFS_H */
