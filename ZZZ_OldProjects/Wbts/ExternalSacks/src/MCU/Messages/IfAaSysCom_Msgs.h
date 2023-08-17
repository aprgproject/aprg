/* *******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2017 Nokia. All rights reserved.
* *******************************************************************************/

#ifndef IF_MCU_AASYSCOM_MSGS_H
#define IF_MCU_AASYSCOM_MSGS_H

#include <CcsCommon.h>
#include <TAaSysComSicad.h>
#include <IfAaSysCom_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
***********************************************************************************
* @addtogroup dgAaSysComMcu AaSysCom Messages
* @ingroup  dgAaSysCom
*/
/*@{*/


/**
 * @name Message IDs in AaSysCom MCU
 *
 * @{
 */

#define AASYSCOM_LMSGW_ADDREROUTING_REQ_MSG         0x13F0    /**< Message sent to add Large Messages rerouting info */
#define AASYSCOM_LMSGW_DELREROUTING_REQ_MSG         0x13F1    /**< Message sent to remove Large Message rerouting info */

#define AASYSCOM_LMSGW_ADDREROUTING_RESP_MSG        0x14F0    /**< Message sent as a response on AASYSCOM_LMSGW_ADDREROUTING_REQ_MSG */
#define AASYSCOM_LMSGW_DELREROUTING_RESP_MSG        0x14F1    /**< Message sent as a response on AASYSCOM_LMSGW_DELREROUTING_REQ_MSG */
/** @} */ // Message IDs in AaSysCom


/**
 * @name Message structures used in AaSysCom MCU.
 *
 * @{
 */

/**
 * @brief Message structure used for adding/removing rerouting info for Large Messages
 **/
typedef struct SAaSysComLargeMsgReroutingInfo
{
    TAaSysComSicad        rerouteSicad;             /**< Local address to be re-routed */

#if defined (CCS_LITTLE_ENDIAN)
    u16                   reserved;
    TAaSysComNid          targetNid;                /**< Target node id */
#elif defined (CCS_BIG_ENDIAN)
    TAaSysComNid          targetNid;                /**< Target node id */
    u16                   reserved;
#else
    #error "No endianness defined."
#endif
}SAaSysComLargeMsgReroutingInfo;

/**
 * @brief Message structure used for sending response status for adding/removing rerouting
 *        request for Large Messages.
 *        The structure is used by AASYSCOM_LMSGW_ADDREROUTING_RESP_MSG
 *        and AASYSCOM_LMSGW_DELREROUTING_RESP_MSG messages.
 *  status field takes EAaSysComLargeMsgReroutingStatus_OK on success.
 **/
typedef struct SAaSysComLargeMsgReroutingInfoStatus
{
    struct SAaSysComLargeMsgReroutingInfo   reroutingInfo;   /**< original request message */
    EAaSysComLargeMsgReroutingStatus        status;          /**< status of rerouting info for add/remove request */
} SAaSysComLargeMsgReroutingInfoStatus;

/* @}*/ // Message structures used in AaSysCom MCU.
/* @}*/ // dgAaSysComMcu AaSysCom Messages

#ifdef __cplusplus
}
#endif

#endif // IF_MCU_AASYSCOM_MSGS_H
