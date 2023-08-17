/**
*******************************************************************************
* @brief                 AaSysComGw messages header
* @module                AaSysComGw
*
* Copyright 2015 Nokia Networks. All rights reserved.
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef IF_COMMON_AASYSCOMGW_MSGS_H
#define IF_COMMON_AASYSCOMGW_MSGS_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaSysComGw_Defs.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComGwCommon AaSysComGw Common
 * @ingroup dgAaSysCom
 * @{
 */


/** @name GW Messages
 * @{
 */
#ifndef AASYSCOM_GW_UNKNOWN_SENDER_MSG
# define AASYSCOM_GW_UNKNOWN_SENDER_MSG          0x2BD7 /* !- SIGNO(struct AaSysComGwUnknownSenderInd) -! */
#endif /* AASYSCOM_GW_UNKNOWN_SENDER_MSG */
/** @} */

/** @name Message structure definitions
 * @{
 */
/**
 * @brief Message with unknown sender
 *
 * This message is sent to the registrated default receiver incase route
 * mapping information for message sender does not exist is GW.
 * @note If default receiver is not registrated the message will be
 * ignored with an error log writing.
 */
typedef struct AaSysComGwUnknownSenderInd
{
  /** IP address and port of the original message sender */
  SAaSysComGwIpAddress_deprecated sender;
  /** following field is a special field ment for users to be able to point
      to the place in the message, where the actual message data starts
      (array of 4 bytes to make the struct padding divisible by 4). Length
      of data is api_header.length - sizeof(struct Api_header) */
  u8 data[4]; /* dummy message payload accessory field */
} AaSysComGwUnknownSenderInd CCS_DEPRECATED("Use AaSysComGwUnknownSenderIndExt instead.");
/** @} */

/** @} end: @addtogroup dgAaSysComGwCommon AaSysComGw Common */

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOMGW_MSGS_H */
