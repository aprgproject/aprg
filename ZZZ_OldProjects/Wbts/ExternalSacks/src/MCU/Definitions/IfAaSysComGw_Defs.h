/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_AASYSCOMGW_DEFS_H
#define IF_MCU_AASYSCOMGW_DEFS_H

#include <CcsCommon.h>
#include "../../COMMON/Definitions/IfAaSysComGw_Defs.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaSysComGw_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComGwMcu AaSysComGw MCU
 * @ingroup dgAaSysCom
 *
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/** @name Interface types (MCU specific)
 * @{
 */

/** @brief GW UDPCP packets priority

    SysComGW UDPCP support: Priority Code Point (PCP) for all packets to be sent via UDPCP socket.
    PCPs between 0 (lowest) and 7 (highest) are allowed.
    If not set, system value will be used (priority will not be changed). */
#define AASYSCOM_CONFIG_TAG_GW_UDPCP_PACKETS_PRIORITY   "ccs.service.aasyscom.gw.udpcp.packets_priority"

/** @brief GW TCP maximum amount of routes

    This configuration tag is obsolete and not used any more.
    Number of TCP route is limited only by maximum number of SysComGw routes allowed in system. */
#define AASYSCOM_CONFIG_TAG_GW_TCP_MAX_ROUTES           "ccs.service.aasyscom.gw.tcp.max_routes"

/** @brief GW SCTP RTO.Initial

    SysComGW SCTP support: Retransmission time out (RTO) - initial value (RFC 4960: RTO.Initial)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_RTO_INITIAL         "ccs.service.aasyscom.gw.sctp.rto_initial"

/** @brief GW SCTP RTO.Min

    SysComGW SCTP support: Retransmission time out (RTO) - minimal value (RFC 4960: RTO.Min)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_RTO_MIN             "ccs.service.aasyscom.gw.sctp.rto_min"

/** @brief GW SCTP RTO.Max

    SysComGW SCTP support: Retransmission time out (RTO) - maximal value (RFC 4960: RTO.Max)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_RTO_MAX             "ccs.service.aasyscom.gw.sctp.rto_max"

/** @brief GW SCTP Max.Init.Retransmits

    SysComGW SCTP support: Maximum number of retransmissions during association establishment (RFC 4960: Max.Init.Retransmits)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_MAX_INIT_RETRANSMISSIONS        "ccs.service.aasyscom.gw.sctp.max_init_retransmisions"

/** @brief GW SCTP Association.Max.Retrans

    SysComGW SCTP support: Maximum number of retransmissions before association is considered broken (RFC 4960: Association.Max.Retrans)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_ASSOCIATION_MAX_INIT_RETRANS    "ccs.service.aasyscom.gw.sctp.association_max_retrans"

/** @brief GW SCTP HB.interval

    SysComGW SCTP support: Interval between heart beats (RFC 4960: HB.interval)
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_HB_INTERVAL         "ccs.service.aasyscom.gw.sctp.hb_interval"

/** @brief GW SCTP SACK timeout

    SysComGW SCTP support: Maximum delay time (in milliseconds) before SACK (selective acknowledgement) message is sent
    If not set, default value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_SACK_TIMEOUT        "ccs.service.aasyscom.gw.sctp.sack_timeout"

/** @brief GW SCTP One-to-One socket style interface

    SysComGW SCTP support: One-to-Many (value 0) and One-to-One (value 1) socket style interfaces
    (RFC 6458: One-to-Many Style Interface and One-to-One Style Interface)
    Obsolete from LBT3430 (SysCom SCTP improvement).
    If not set, One-to-Many style interface will be used. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_ONE_TO_ONE "ccs.service.aasyscom.gw.sctp.one_to_one"

/** @brief GW SCTP Disable Path MTU Discovery (PMTUD_DISABLE)

    SysComGW SCTP support: 0 - PMTUD_DISABLE will not be added to spp_flags,
                           Otherwise - PMTUD_DISABLE will be added to spp_flags
    (RFC 6458: 8.1.12. Peer Address Parameters (SCTP_PEER_ADDR_PARAMS))
    If not set, SPP_PMTUD_DISABLE will not be added to spp_flags in SCTP_PEER_ADDR_PARAMS. */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_PMTUD_DISABLE "ccs.service.aasyscom.gw.sctp.pmtud_disable"

/** @brief GW SCTP Maximum Fragmentation Size (SCTP_MAXSEG)

    SysComGW SCTP support: 0 - do not limit fragmentation (PMTU will affect SCTP's choice of DATA chunk size),
                           Otherwise - maximum size in bytes to put in any outgoing SCTP DATA chunk.
    (RFC 6458: 8.1.16. Get or Set the Maximum Fragmentation Size (SCTP_MAXSEG)
    If not set, default value will be used (0 - do not limit fragmentation). */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_MAXSEG "ccs.service.aasyscom.gw.sctp.maxseg"

/** @brief GW SCTP Send Buffer Size
    SCTP socket send buffer size in bytes. Set via setsockopt for all SCTP sockets created in GW
    Value <= 0 means system default */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_SNDBUFSIZE "ccs.service.aasyscom.gw.sctp.sndbufsize"

/** @brief GW SCTP Receive Buffer Size
    SCTP socket receive buffer size in bytes. Set via setsockopt for all SCTP sockets created in GW
    Value <= 0 means system default */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_RCVBUFSIZE "ccs.service.aasyscom.gw.sctp.rcvbufsize"

/** @brief GW SCTP Control Threads Amount
    SysComGW SCTP support: 0 - use default value (one control thread),
                           Otherwise - the amount of control threads.
    If not set, default value will be used (one control thread). */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_THREADS_AMOUNT "ccs.service.aasyscom.gw.sctp.threads_amount"

/** @brief GW SCTP Message Life Time
  SysComGW SCTP support: 0 - use default value (500 ms),
                         Otherwise - the SCTP's message life time.
  If not set, default value will be used (500 ms). */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_MSG_LIFETIME "ccs.service.aasyscom.gw.sctp.msg_lifetime"

/** @brief GW SCTP DSCP
  SysComGW SCTP support: 0 - use default value (0),
                         Otherwise - the DSCP value (6-bit field; RFC 2474).
  If not set, default value will be used (0). */
#define AASYSCOM_CONFIG_TAG_GW_SCTP_DSCP "ccs.service.aasyscom.gw.sctp.dscp"

/** @brief GW IPv6 support

    SysComGW IPv6 support: Disabled (value 0) and Enabled (value 1)
    On linux_arm53_le, linux_arm57_le and linux_x86_64 support for
    IPv6 is enabled by default.
    Other build variants by default do not support IPv6.
    Please notice, IPv6 must by supported by underlying OS (in case of RP SW it is LFS)
    to manage it correctly inside CC&S. */
#define AASYSCOM_CONFIG_TAG_GW_IPV6_ENABLED "ccs.service.aasyscom.gw.ipv6.enabled"

/** @brief GW TCP Message Life Time
  SysComGW TCP support: 0 - use default value (500 ms),
                         Otherwise - the TCP's message life time in ms.
  If not set, default value will be used (500 ms). */
#define AASYSCOM_CONFIG_TAG_GW_TCP_MSG_LIFETIME "ccs.service.aasyscom.gw.tcp.msg_lifetime"

/** @brief GW TCP Control Threads Amount
    SysComGW TCP support: 0 - use default value (one control thread),
                          Otherwise - the amount of control threads.
                          The maximum number of control threads is 1000.
    If not set, default value will be used (one control thread). */
#define AASYSCOM_CONFIG_TAG_GW_TCP_THREADS_AMOUNT "ccs.service.aasyscom.gw.tcp.threads_amount"

/** @brief GW TCP Send Buffer Size
    TCP socket send buffer size in bytes. Set via setsockopt for all TCP sockets created in GW
    Value <= 0 means system default */
#define AASYSCOM_CONFIG_TAG_GW_TCP_SNDBUFSIZE "ccs.service.aasyscom.gw.tcp.sndbufsize"

/** @brief GW TCP Receive Buffer Size
    TCP socket receive buffer size in bytes. Set via setsockopt for all TCP sockets created in GW
    Value <= 0 means system default */
#define AASYSCOM_CONFIG_TAG_GW_TCP_RCVBUFSIZE "ccs.service.aasyscom.gw.tcp.rcvbufsize"

/** @brief GW TCP Control Connection Behavior
    This flag is used only in case of TCP client route.
    Setting this flag to GLO_TRUE postpone connection to peer to the first sending data via route.
    If not set or set to GLO_FALSE (default behavior) connection to peer is establish just after route is added. */
#define AASYSCOM_CONFIG_TAG_GW_TCP_POSTPONE_CONNECTION "ccs.service.aasyscom.gw.tcp.postpone_connection"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.gw.allow.udp.broadcast
*
* Direction:        input
*
* Description:      If value of this tag is 1 then UDP broadcast is enabled and
*                   SysComGw can send UDP broadcast messages. By default it is disabled.
*
* Effect analysis:  If not set, UDP broadcast is disabled.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AASYSCOM_CONFIG_TAG_GW_ALLOW_UDP_BROADCAST
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_GW_ALLOW_UDP_BROADCAST "ccs.service.aasyscom.gw.allow.udp.broadcast"

/** @brief GW UDPCP tasks scheduler
 *  SysComGW supports: 0 - EAaProEuSchedulingPolicy_RealTime
 *                     1 - EAaProEuSchedulingPolicy_Background
 *  If not set, EAaProEuSchedulingPolicy_RealTime value will be used. */
#define AASYSCOM_CONFIG_TAG_GW_UDPCP_TASK_SCHEDULER "ccs.service.aasyscom.gw.udpcp.task.scheduler"

/**
 * ******************************************************************************
 * *
 * * @verbatim
 * * Tag name:         ccs.service.aasyscom.gw.non_separate_applicaton
 * *
 * * Direction:        input
 * *
 * * Description:      If value of this tag is 1 SysCom message routing realized by AaSysComGw service
 * *                   is performed inside CCSDaemonExe application.
 * *                   If value of this tag is 0 SysCom message routing realized by AaSysComGw service
 * *                   is performed inside dedicated CCSSysComGwExe application.
 * *                   By default 0 is used.
 * *
 * * Effect analysis:  If not set, default behavior is realized.
 * *
 * * Restriction:      none
 * *
 * * Value:            IE Type:     Size:     Range:
 * *                   number       u32       <0, 1>
 * *
 * * Define:           AASYSCOM_CONFIG_TAG_GW_NON_SEPARATE_APPLICATION
 * *
 * * See:              none
 * * @endverbatim
 * *****************************************************************************/
#define AASYSCOM_CONFIG_TAG_GW_NON_SEPARATE_APPLICATION "ccs.service.aasyscom.gw.non_separate_applicaton"

/** @brief SIC mask length for the board ID part */
#define AASYSCOM_GW_SICMASKLEN_BOARD_ID     8
/** @brief SIC mask length for the board ID and SOC ID part */
#define AASYSCOM_GW_SICMASKLEN_BOARD_SOC_ID 12
/** @brief SIC mask length for the node ID part */
#define AASYSCOM_GW_SICMASKLEN_NODE_ID      16
/** @brief SIC mask length for exact match of entire address */
#define AASYSCOM_GW_SICMASKLEN_SIC          32

/** @} */

/** @} end: @addtogroup dgAaSysComGwMcu AaSysComGw MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOM_DEFS_H */
