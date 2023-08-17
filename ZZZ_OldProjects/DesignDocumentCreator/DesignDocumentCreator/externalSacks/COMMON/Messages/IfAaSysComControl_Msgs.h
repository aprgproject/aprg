/** @file
*   @brief AaSysComControl message structures definitions
*
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2016 Nokia. All rights reserved.$
*/


#ifndef IF_COMMON_AASYSCOMCONTROL_MSGS_H
#define IF_COMMON_AASYSCOMCONTROL_MSGS_H

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaSysComControl_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 */


/**
 * @name Message structures used in AaSysComControl.
 *
 * @{
 */

/** @brief SysCom Echo Route Request message structure. */
typedef struct SAaSysComEchoRouteReq
{
    SAaSysComTimeStampInTwoWords senderTimeStamp; /**< senderTimeStamp,
     orignal sender sets */
#if defined CCS_LITTLE_ENDIAN
    u16 echoDataSize; /**< echoDataSize, size of echoData in octets
     see comment at the end of this structure */
    u16 padding; /**< to set length divisible by 4 */
    u8 receiverIndex; /**< receiverIndex, 0..254 */
    u8 receiverCount; /**< receiverCount, 1..255 */
    u8 sequenceNumber; /**< sequenceNumber for application */
    u8 reserved; /**< not used currently */
#else
    u16 padding; /**< to set length divisible by 4 */
    u16 echoDataSize; /**< echoDataSize, size of echoData in octets
     see comment at the end of this structure */
    u8 reserved; /**< not used currently */
    u8 sequenceNumber; /**< sequenceNumber for application */
    u8 receiverCount; /**< receiverCount, 1..255 */
    u8 receiverIndex; /**< receiverIndex, 0..254 */
#endif
    SEchoRouteReceiver receiverAddr[1]; /**< receiverAddr, placeholder, can contain up to max receivers
     last receiver is the final destination */
    SAaSysComTimeStampInTwoWords receiverTimeStamp[1]; /**< receiverTimeStamp, placeholder, can contain up to max timestamps */
    /**< echoData added after the last receiverTimeStamp, size is limited by the dynamic tables in the message strucure above
     and alltogether the maximum is limited by SysCom message length */
    /* Length of the message is automatically padded by
     AaSysComControlCalculateEchoRouteMsgLen() to be divisible by 4 */

} SAaSysComEchoRouteReq;

/** @} */
/** @} end: @addtogroup dgAaSysComCommon AaSysCom Common */

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOMCONTROL_MSGS_H */
