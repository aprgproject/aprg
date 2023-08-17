/** @file
*   @brief MCU specific AaSysCom definitions for use in SysCom
*   @copyright 2015 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef IF_MCU_AASYSCOM_DEFS_H
#define IF_MCU_AASYSCOM_DEFS_H

#include <CcsCommon.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include "../../COMMON/Definitions/IfAaSysCom_Defs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComMcu AaSysCom MCU
 * @ingroup dgAaSysCom
 * @{
 */

/** @name Type definitions
 *
 * @{
 */
typedef u32 TAaSysComLargeMsgSize;     /**< SysCom large message size. */

/** @} */

/** @name Following AaConfig tags are supported by AaSysCom on MCU
 *
 * @{
 */

/** @brief The size of message pool in the system (in Megabytes).

    Value type is u32. Default value is 4.
    If not set, default value will be used. Please use very carefully!
    Message Pool Size must be included in CC&S memory budget. */
#define   AASYSCOM_CONFIG_TAG_MESSAGE_POOL_SIZE "sys.ce.msgpool.size"

/**
******************************************************************************
* @brief Type of used memory for message pool
*
* Tag name:         sys.ce.msgpool.cma.enabled
*
* Direction:        input
*
* Description:      Type of used memory for message pool. By default it is shared memory.
*                   CMA memory can be enabled only on Kepler2 targets.
*
* Effect analysis:  If not set, default value will be used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AASYSCOM_CONFIG_TAG_MESSAGE_POOL_CMA_ENABLED
*
* See:              none
*****************************************************************************/
#define   AASYSCOM_CONFIG_TAG_MESSAGE_POOL_CMA_ENABLED "sys.ce.msgpool.cma.enabled"

/** @brief The size of the pool for large messages in the system (in megabytes).

    Value type is u32.
    Default value is 0, which means no large message can be created or received from another node.
    If not set, default value will be used, effecitvely disabling SysCom extension for large messages.
    Please use very carefully! Large Message Pool Size must be included in CC&S memory budget. */
#define   AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_POOL_SIZE "sys.ce.largemsgpool.size"

/** @brief Maximum payload size of large message that can be created or received in the system (in bytes).

    Value type is u32.
    Default value is 0, which means the size of the pool for large messages is the only limitation.
    If not set, default value will be used. */
#define   AASYSCOM_CONFIG_TAG_LARGE_MESSAGE_MAXSIZE "sys.ce.largemsgpool.maxmsgsize"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.uds.folder.path
*
* Direction:        input
*
* Description:      Location of the folder where UDS files are stored.
*
* Effect analysis:  If not set, UDS support will be disabled.
*
* Restriction:      UDS functionality is not available on FSMr2
*
* Value:            IE Type:                    Size:       Range:
*                   zero-terminated string      N/A         N/A
*
* Define:           AASYSCOM_CONFIG_TAG_UDS_FOLDER_PATH
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_UDS_FOLDER_PATH "ccs.service.aasyscom.uds.folder.path"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.socketlink.rx.buffersize
*
* Direction:        input
*
* Description:      Size of main receive buffer size in AaSysComSocketLink
*
* Effect analysis:  If not set, buffer size will be not set and default value from system will be taken.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <1, 4294967295>
*
* Define:           AASYSCOM_CONFIG_TAG_SOCKET_LINK_RX_BUFFERSIZE
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_SOCKET_LINK_RX_BUFFERSIZE "ccs.service.aasyscom.socketlink.rx.buffersize"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.socketlink.sending_in_eu_context
*
* Direction:        input
*
* Description:      This flag enables/disables sending SysCom messages in
*                   EU context and it concerns only messages routed via
*                   AASYSCOM_SOCKET_LINK. As default it is enabled.
*
* Effect analysis:  If not set, all messages routed via syscom socket are sent
*                   in EU context.
*
* Restriction:      Concerns only messages routed via AASYSCOM_SOCKET_LINK.
*                   Value of this tag is check only in startup phase.
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AASYSCOM_CONFIG_TAG_SOCKETLINK_SEDING_IN_EU_CONTEXT
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_SOCKETLINK_SEDING_IN_EU_CONTEXT "ccs.service.aasyscom.socketlink.sending_in_eu_context"

/**
*  @brief AaIPC mode - which service is used for local syscom communication. Used in \ref AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE
*  @see
*                   AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE
*/
typedef enum AaIPCMode
{
    AaIPCMode_RTOS  = 0, /**< use AaRTOS */
    AaIPCMode_IPC   = 1 /**< use AaIPC */
} AaIPCMode;

/**
******************************************************************************
*
* @brief This tag defines which service is used for local syscom communication
* Tag name:         ccs.service.aasyscom.local.communication.mode
*
* Direction:        input
*
* Description:      This tag defines which service is used for local syscom communication.
*                   \li \ref AaIPCMode_RTOS (default)
*                   \li \ref AaIPCMode_IPC
*
* Effect analysis:  If not set, local syscom communication is routed via AaRTOS
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       \ref AaIPCMode
*
* Define:           AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE
*
* @see
*                   AaIPCMode
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE "ccs.service.aasyscom.local.communication.mode"

/**
******************************************************************************
*
* @brief This tag defines how many huge pages are configured
* Tag name:         sys.mem.huge_pages.count
*
* Direction:        input
*
* Description:      This tag defines how many huge pages are configured.
*                   0: use system default huge pages count (default)
*
* Effect analysis:  If not set, use system default huge pages count
*
* Restriction:      Only used if AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE is set to AaIpc mode
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 4294967295>
*
* Define:           AACONFIG_TAG_SYS_MEM_HUGE_PAGES_COUNT
*
* @see
*                   AASYSCOM_CONFIG_TAG_LOCAL_COMMUNICATION_MODE
*****************************************************************************/
#define AACONFIG_TAG_SYS_MEM_HUGE_PAGES_COUNT "sys.mem.huge_pages.count"

/**
 * @brief UDS Link Server CPID value.
 */
#define   AASYSCOM_UDS_LINK_SERVER_CPID 0x0647

/**
 * @brief UDS Link Server ID/CPID value.
 * @note This value is used as linkId and CPID for UDS server link.
 */
#define   AASYSCOM_UDS_LINK_SERVER AASYSCOM_UDS_LINK_SERVER_CPID

/**
 * @brief UDS Link Client CPID value.
 */
#define   AASYSCOM_UDS_LINK_CLIENT_CPID 0x0648

/**
 * @brief UDS Link Client ID/CPID value.
 * @note This value is used as linkId and CPID for UDS client link.
 */
#define   AASYSCOM_UDS_LINK_CLIENT AASYSCOM_UDS_LINK_CLIENT_CPID

/**
 * @brief SysCom Socket Link CPID value.
 */
#define   AASYSCOM_SOCKET_LINK_CPID 0x0649

/**
 * @brief SysCom Socket Link ID/CPID value.
 * @note This value is used as linkId and CPID for SysCom Socket Link.
 */
#define   AASYSCOM_SOCKET_LINK AASYSCOM_SOCKET_LINK_CPID

/**
 * SysCom header delivery order bit macros
 */
#define AASYSCOM_EXTFLAGS_DELIVERY_ORDER_BIT_MASK           (0x0008)
#define AASYSCOM_EXTFLAGS_DELIVERY_ORDER_BIT_CLEAR_MASK     CCS_STATIC_CAST(u16,(~AASYSCOM_EXTFLAGS_DELIVERY_ORDER_BIT_MASK))
#define AASYSCOM_EXTFLAGS_GET_DELIVERY_ORDER_BIT(A)         CCS_STATIC_CAST(u16,(((A) & AASYSCOM_EXTFLAGS_DELIVERY_ORDER_BIT_MASK) >> 3))

/**
 *  @brief AaSysCom Large Message rerouting status return codes.
 */
typedef enum EAaSysComLargeMsgReroutingStatus {
    EAaSysComLargeMsgReroutingStatus_OK                     = 0, /**< success, no error */
    EAaSysComLargeMsgReroutingStatus_Unknown                = 1, /**< unknown/not classified error */
    EAaSysComLargeMsgReroutingStatus_NoInfoExists           = 2, /**< no rerouting info found */
    EAaSysComLargeMsgReroutingStatus_InfoAlreadyExists      = 3, /**< rerouting info exists */
    EAaSysComLargeMsgReroutingStatus_InvalidParameter       = 4, /**< invalid parameter */
    EAaSysComLargeMsgReroutingStatus_InfoLimit              = 5  /**< max rerouting infos already configured */
} EAaSysComLargeMsgReroutingStatus;

/*
 * @brief AaSysCom message info
 */
typedef struct SAaSysComMessageInfo
{
    TAaSysComMsgId msgId;           /**< syscom message identifier */
    TAaSysComMsgSize msgSizeBytes;  /**< syscom message size in bytes */
    u64 msgQueueingTimeUs;          /**< time that message was kept in EU's message queue (in us) */
} SAaSysComMessageInfo;

/** @} */

/** @} end: @addtogroup dgAaSysComMcu AaSysCom MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOM_DEFS_H */
