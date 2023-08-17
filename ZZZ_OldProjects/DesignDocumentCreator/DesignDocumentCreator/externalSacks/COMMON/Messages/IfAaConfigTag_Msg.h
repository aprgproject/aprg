/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_TAG_MSG_H_
#define _COMMON_IF_AACONFIG_TAG_MSG_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfigTag_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagMsg AaConfigTag messages
 * @ingroup dgAaConfigTag
 */

/**
 * @defgroup dgAaConfigTagMsgCommon AaConfigTag common messages
 * @ingroup dgAaConfigTagMsg
 */

/**
 * @defgroup dgAaConfigTagMsgCommonInt AaConfigTag common internal messages
 * @ingroup  dgAaConfigTagMsgCommon
 *
 * These messages are available for CC&S internal users.
 */
/*@{*/

/** Config tag public set notification */
#define AACONFIG_TAG_PUBLIC_SET_NOTIF_MSG       0x08E6      /* !- SIGNO(struct SAaConfigTagPublicSetNotifMsg) -!  */
/** Config tag public delete notification */
#define AACONFIG_TAG_PUBLIC_DELETE_NOTIF_MSG    0x1B96      /* !- SIGNO(struct SAaConfigTagPublicDeleteNotifMsg) -!  */
/** Subscribe for config tag public set notification request */
#define AACONFIG_TAG_SUBSCRIBE_PUBLIC_SET_MSG   0x0BE6      /* !- SIGNO(struct void) -! */
/** Subscribe config tag public set notification response */
#define AACONFIG_TAG_SUBSCRIBE_PUBLIC_SET_RESP_MSG 0x0BE7   /* !- SIGNO(struct void) -! */
/** Unubscribe for config tag public set notification request */
#define AACONFIG_TAG_UNSUBSCRIBE_PUBLIC_SET_MSG 0x1F26      /* !- SIGNO(struct void) -! */

/*@}*/

/** @brief Config tag public set notification. */
typedef struct SAaConfigTagPublicSetNotifMsg
{
  char           name[AACONFIG_TAG_MAX_NAME_LENGTH];                /**< name of config tag */
  u32            vlen;                                              /**< length of value */
  EAttributeType type;                                              /**< type of config tag */
  u8             value[1];                                          /**< value of config tag */
} SAaConfigTagPublicSetNotifMsg;

/** @brief Config tag public delete notification. */
typedef struct SAaConfigTagPublicDeleteNotifMsg
{
  char  name[AACONFIG_TAG_MAX_NAME_LENGTH];        /**< name of config tag */
} SAaConfigTagPublicDeleteNotifMsg;

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_TAG_MSG_H_
