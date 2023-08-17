/** @file
*   @brief Common AaSysCom definitions
*   @copyright 2016 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef IF_COMMON_AASYSCOM_DEFS_H
#define IF_COMMON_AASYSCOM_DEFS_H

#include <TAaSysComSicad.h>
#include <glo_def.h>
#include <CcsCommon.h>
#include <EStatus.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 */

/**
 *
 * Runtime configuration can be divided into pre- and post-configuration phases.
 * Pre-configuration takes place before CE startup has been done for a service.
 * Post-configuration takes place after CE, EE and EU startup. Configuration is
 * handled using so called configuration tags. Data and keys are variable
 * width in size so they are quite flexible to use.
 * \n\n
 * Usually configuration tags are used for input direction i.e. feeding
 * configuration to CC&S service. However some tags can also be used for output
 * direction i.e. for advertising CC&S service state or capabilities. Configuration
 * tag description should state wether the tag is inteded for feeding information
 * (input) to the service or the service uses the tag for capability and state
 * advertisement (output).
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.ownnid
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets own node id, value type is TAaSysComNid, syscom will
 *                   not be able to route messages outside before this is set
 *                   and AaSysComGetOwnNid() will return AASYSCOM_NODE_INVALID
 *                   before set is done.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     From SysCom viepoint reserved values AASYSCOM_NODE_ANY,
 *                   AASYSCOM_NODE_NONE, AASYSCOM_NODE_LOCAL, AASYSCOM_NODE_MASTER
 *                   (defined in IfAaSysCom.h).
 *                   From system viepoint there are nodeId spaces for each subsytem.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_OWNNID
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.partner.nid
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets partner node ID. Value type is TAaSysComNid. SysCom will not be able to
 *                   route messages inside CellVM between two CC&S before this is set. Only for RCP usage.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     Only for RCP usage. From SysCom viepoint reserved values AASYSCOM_NODE_ANY,
 *                   AASYSCOM_NODE_NONE, AASYSCOM_NODE_LOCAL, AASYSCOM_NODE_MASTER
 *                   (defined in IfAaSysCom.h).
 *                   From system viepoint there are nodeId spaces for each subsytem.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_PARTNER_NID
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.masternid
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets master node id, value type is TAaSysComNid, messages
 *                   cannot be send with AASYSCOM_NODE_MASTER0 before this is
 *                   set.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     From SysCom viepoint reserved values AASYSCOM_NODE_ANY,
 *                   AASYSCOM_NODE_NONE, AASYSCOM_NODE_LOCAL, AASYSCOM_NODE_MASTER
 *                   (defined in IfAaSysCom.h).
 *                   From system viepoint there are nodeId spaces for each subsytem.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_MASTERNID
 *
 *  See:             None
 * @endverbatim
 */

/** @name Following AaConfig tags are supported by the AaSysCom common
 *
 * @{
 */

/** Sets own node ID. Value type is TAaSysComNid. SysCom will not be able to
 route messages outside before this is set and AaSysComGetOwnNid() will
 return AASYSCOM_NODE_INVALID before set is done. */
#define AASYSCOM_CONFIG_TAG_OWNNID "ccs.service.aasyscom.ownnid"

/** Sets partner node ID. Value type is TAaSysComNid. SysCom will not be able to
 route messages inside CellVM between two CC&S before this is set. Only for RCP usage */
#define AASYSCOM_CONFIG_TAG_PARTNER_NID "ccs.service.aasyscom.partner.nid"

/** Sets master node ID. Value type is TAaSysComNid. Messages cannot be sent
 with AASYSCOM_NODE_MASTER0 before this is set. */
#define AASYSCOM_CONFIG_TAG_MASTERNID "ccs.service.aasyscom.masternid"

/** Sets logical node ID. Value type is TAaSysComNid. Messages cannot be sent
 to active board in redundancy system before this is set. */
#define AASYSCOM_CONFIG_TAG_LOGICALNID "ccs.service.aasyscom.logicalnid"
/** @} */

/**
 * @name AaSysComMsgReceive wait times
 * @{
 */
#define AASYSCOM_INFINITE_WAITTIME 0xFFFFFFFF  /**< Infinite wait time. */
#define AASYSCOM_NO_WAITTIME 0                 /**< No waiting. */
/** @} */

/**
 * @name AaSysCom ID definitions
 * @{
 */
/** @brief Invalid/unspecified communication point. */
#define AASYSCOM_CP_INVALID   0x0000

/** @brief Any communication point. */
#define AASYSCOM_CP_ANY       0xFFFF

/** @brief None communication point.

 When no CPID can be allocated for a communicating entity or the entity has
 no means whatsoever to find out its own communication point identifier the
 entity can use this identifier value as its CPID when sending messages.
 However, all messages sent to this communication point are discarded
 regardless of the node identifier in the receiver SIC address. */
#define AASYSCOM_CP_NONE      0xFFFE

/** @brief Invalid/unspecified SIC node ID. */
#define AASYSCOM_NODE_INVALID 0x0000

/** @brief Any SIC node ID. */
#define AASYSCOM_NODE_ANY     0xFFFF

/** @brief None SIC node ID. */
#define AASYSCOM_NODE_NONE    0xFFFE

/** @brief Local node ID.

 Local-alias can be used when the real node identifier of the user's node is
 not known or does not need to be known. */
#define AASYSCOM_NODE_LOCAL   0x0F01

/** @brief Master node ID.

 Master-alias can be used when the real node identifier of the master node
 is not known. */
#define AASYSCOM_NODE_MASTER  0x0FF0

/** @brief Master node id. Only for backward compatibility. */
#define AASYSCOM_NODE_MASTER0 AASYSCOM_NODE_MASTER

/** @brief Unspecified/invalid SIC address. */
#define AASYSCOM_ADDRESS_INVALID 0x00000000

/** @brief Any SIC address. */
#define AASYSCOM_ADDRESS_ANY  0xFFFFFFFF

/** @brief None SIC address.
 When no SIC address can be allocated for a communicating entity or the
 entity has no means whatsoever to find out its own SIC address the
 entity can use this address as its address when sending messages.
 However, all messages sent to this address are discarded. */
#define AASYSCOM_ADDRESS_NONE       0xFFFEFFFE

/** CPID for the AaSysCom Echo, all other messages except
 AASYSCOM_ECHO_ROUTE_REQ_MSG sent to this CDPI will be echoed back with
 receiver/sender swapped. AASYSCOM_ECHO_ROUTE_REQ_MSG contents are updated
 and forwarded to destination given in the message */
#define AASYSCOM_ECHO_CPID          0x0610

/** CPID for the AaSysCom RTM */
#define AASYSCOM_RTM_CPID           0x0611

/** CPID for the AaSysCom Drain, whch deletes all received messages */
#define AASYSCOM_DRAIN_CPID         0x0612

/** CPID for the AaSysCom Control, which so far (09.10.2008) is more or
 less a placeholder for certain SysCom control features */
#define AASYSCOM_CONTROL_CPID       0x0613

/** CPID used for creating RCV_ONLY routes.
 This is used as defined in LTE1608-M-e1 which is part of LRC Redundancy */
#define AASYSCOM_CP_RCVONLY         0xFFFD


/** @} end: @name AaSysCom ID definitions */

/**
 * @name AaSysCom invalid/unspecified link
 * @{
 */
#define AASYSCOM_LINK_INVALID       0x0000       /**< Invalid/uspecified link */
/** @} */

/**
 * @name AaSysCom link definitions for UP environment
 * @{
 * AaSysCom link definitions for UP environment. These definitions are
 * located in CCS_COMMON_API section because e.g. O&M uses them when
 * utilizing AaSysCom echo feature.
 */
#define AASYSCOM_LINK_C2C           1       /**< Inter-CPU link. */
#define AASYSCOM_LINK_UDP           2       /**< UDP link. */
#define AASYSCOM_LINK_UDPCP         3       /**< UDPCP link. */
#define AASYSCOM_LINK_NON_BIP_UNREL 4       /**< Special link to handle unreliable
                                                 message to LCP as forward to ARM instead
                                                 of BIP message through the XGE. */
#define AASYSCOM_LINK_SRIO          5       /**< SRIO link for Faraday. */
#define AASYSCOM_LINK_RAW_ETH       6       /**< Raw Ethernet link. */
#define AASYSCOM_LINK_SRIO_U_PLANE  7       /**< SRIO user plane link. */
#define AASYSCOM_LINK_SRIO_C_PLANE  8       /**< SRIO control plane link. */
#define AASYSCOM_LINK_SRIO_STREAM_0 9       /**< SRIO stream link 0. */
#define AASYSCOM_LINK_EMC_XGE       10      /**< EM Chaining over XGE link */
#define AASYSCOM_LINK_EMC_SRIO      11      /**< EM Chaining over SRIO link */
/** @} */

/**@name AaSysCom default Time To Live (TTL) value for message (Sic v1)
 * @{
 */
#define AASYSCOM_DEFAULT_TTL 0x0F /* 15 in 4 uppermost bits in header flags */
/** @} */

/**
 * @brief Message transfer mode.
 * @{
 * EAaSysCom_Reliable matches with NMAP reliable transfer mode.
 * EAaSysCom_Basic matches with normal NMAP transfer.
 */
typedef enum EAaSysComMtm
{
  EAaSysComMtm_Reliable = 0, /**< Reliable transfer mode. */
  EAaSysComMtm_Basic         /**< Basic (non-reliable) transfer  mode. */
} EAaSysComMtm;

/** @brief Application payload format of the message. */
typedef enum EAaSysComMsgApf
{
  EAaSysComMsgApf_32Big = 0,            /**< Big endian word format. */
  EAaSysComMsgApf_32Little,             /**< Little endian word format. */
  EAaSysComMsgApf_8Big,                 /**< Big endian byte format. */
  EAaSysComMsgApf_8Little               /**< Little endian byte format. */
} EAaSysComMsgApf;
/** @} */

/**
 * @name AaSysCom common type definitions.
 * @{
 */
typedef u16 TAaSysComMsgId;             /**< SysCom message ID. */
typedef u16 TAaSysComMsgSize;           /**< SysCom message size. */
typedef u16 TAaSysComCpid;              /**< SysCom communication point ID. */
typedef u16 TAaSysComNid;               /**< SysCom node ID. */
typedef u8  TAaSysComDscp;              /**< SysCom DSCP (only 6 bits are used). */
/** @} */

/** Macro for AaSysCom message size. */
#define AASYSCOM_MSG_SIZEOF(msg) CCS_STATIC_CAST(TAaSysComMsgSize,sizeof(msg))


/**
 ********************************************************************************
 * @brief Message structure used for reporting internal communication failure.
 * @{
 * @par Description:
 * This message should be sent to applications registered for receiving
 * communication failure notifications.
 *
 * Applications can register or deregister from receiving this notification via
 * function API: AaSysComRegisterForErrors, AaSysComDeregisterForErrors.
 * Links should use function API AaSysComReportCommError for reporting detected
 * communication errors (message delivery failures) to registered applications.
 *
 * @see  AaSysComRegisterForErrors, AaSysComDeregisterForErrors,
 *       AaSysComReportCommError, ERadCcs_AaSysComCommErrNotifyDisabled
 *******************************************************************************/

/** @brief SysCom endianness (message and host). */
typedef enum EAaSysComEndianness
{
    EAaSysComEndianness_NotDefined = 0,
    EAaSysComEndianness_Little,
    EAaSysComEndianness_Big
} EAaSysComEndianness;

/**
 * EAaSysComSendPriority_Unspecified maps to link's default priority level,
 * which may be high, medium, low, or anything else defined for the link in
 * question. See specifications of the link for more information.
 * The Send Priority is handled comletely indendently from the Message Priority
 * which is an attribute of the message and not the link it is sent on.
 */
typedef enum EAaSysComSendPriority
{
    EAaSysComSendPriority_Unspecified = 0,
    EAaSysComSendPriority_High,
    EAaSysComSendPriority_Medium,
    EAaSysComSendPriority_Low
} EAaSysComSendPriority;

/**
 *  EAaSysComMsgPriority_Unspecified maps to default priority level.
 *  A high priority message will have the high priority bit set in the extended header flags (HF3).
 *  This will be transmitted end-end and can be used by intermediate gateways.
 *  The messgae priority is handled complete independently from the Send Priority
 *  which controls link selection but it not message attribute or transmitted end-end.
 *  An unspecified priority to some priority in message based on link priority - this is unspecified.
 */
typedef enum EAaSysComMsgPriority
{
    EAaSysComMsgPriority_Unspecified = 0,
    EAaSysComMsgPriority_Low         = 1,
    EAaSysComMsgPriority_Medium      = 2,
    EAaSysComMsgPriority_High        = 3
} EAaSysComMsgPriority;

/**
 *  AaSysComMsgGetDscp() return codes.
 */
typedef enum EAaSysComMsgGetDscpReturnCode
{
    EAaSysComMsgGetDscpReturnCode_Ok = 0,
    EAaSysComMsgGetDscpReturnCode_DscpNotSet
} EAaSysComMsgGetDscpReturnCode;

/**
 * @brief QoS class attached to the link.
 * THIS TYPE IS DEPRECATED, DO NOT USE!
 * Use EAaSysComQos instead.
 */
typedef enum EAaSysComLinkQos
{
    EAaSysComLinkQos_Reliable = 0, /**< Reliable link. */
    EAaSysComLinkQos_Unreliable /**< Unreliable link. */
} EAaSysComLinkQos;

/** @brief QoS class */
typedef enum EAaSysComQos
{
    EAaSysComQos_Reliable = 0, /**< Reliable. */
    EAaSysComQos_Unreliable /**< Unreliable. */
} EAaSysComQos;

/** @brief Message identifier group of the message. */
typedef enum EAaSysComMsgIdGroup
{
    EAaSysComMsgIdGroup_0 = 0, /**< Normal NMAP/Sack-messages. */
    EAaSysComMsgIdGroup_1 /**< Rhapsody internal events. */
} EAaSysComMsgIdGroup;

/** @brief Message envelope format. */
typedef enum EAaSysComMsgMef
{
    EAaSysComMsgMef_NMAP = 0, /**< NMAP compiant */
    EAaSysComMsgMef_Reserved, /**< Reserved */
    EAaSysComMsgMef_Reserved2, /**< Reserved */
    EAaSysComMsgMef_Sicv1WithTrailer /**< SIC v1 With Trailer */
} EAaSysComMsgMef;

/** @brief SysCom return codes. */
typedef enum EAaSysComReturnCode
{
    EAaSysComReturnCode_Ok = 0, /**< Ok. */
    EAaSysComReturnCode_InvalidCpid, /**< Invalid CPID. */
    EAaSysComReturnCode_InvalidNid, /**< Invalid node ID. */
    EAaSysComReturnCode_InvalidLink, /**< Invalid link. */
    EAaSysComReturnCode_HopNotFound, /**< Hop not found. */
    EAaSysComReturnCode_NbrOf /**< Always the last one. */
} EAaSysComReturnCode;
/** @} */

/**@name AaSysCom common type definitions.
 * @{
 */
typedef u32 TAaSysComHopId; /**< SysCom Hop ID. */
typedef u32 TAaSysComLinkId; /**< SysCom Link ID. */
/**
 * @}
 */

/** @brief Maximum number of nodes in echo route request message. */
#define AASYSCOM_MAX_NMBR_OF_ECHO_ROUTE_NODES   255
/** @brief SysCom Control scheduler options.
 * @{
*/

typedef enum ESchedulerType
{
    ESchedulerType_Default = 0, /**< ESchedulerType_Default, default scheduler */
    ESchedulerType_Fifo, /**< ESchedulerType_Fifo, fifo scheduler */
    ESchedulerType_NbrOf /**< ESchedulerType_NbrOf, last item of enum */
} ESchedulerType;

/** @brief Status of performed operation. */
typedef enum EAaSysComControlStatus
{
    EAaSysComControlStatus_Ok = 0, /**< Success, no error. */
    EAaSysComControlStatus_Failed = 1, /**< Operation failed. */
    EAaSysComControlStatus_InvalidEuId = 2 /**< Requester's euId could not be found. */
} EAaSysComControlStatus;
/** @} */


/** @brief Node ID structure padded for 32 bits. */
typedef struct SAaSysComControlNode
{
#if defined (CCS_LITTLE_ENDIAN)
    TAaSysComNid nodeId; /**< nodeId */
    u16 padding; /**< padding for 32-bit alignment */
#elif defined (CCS_BIG_ENDIAN)
    u16 padding; /**< padding for 32-bit alignment */
    TAaSysComNid nodeId; /**< nodeId */
#endif
} SAaSysComControlNode;

/*
 * @name Structure definitions
 * @{
 *
 * @par Restrictions:
 * Users should not rely on any of these structures as these are only meant
 * for syscom internal use and can change without any notice.
 */

/* AaSysCom application payload read mask  */
#define AASYSCOM_APF_READ_MASK      0x000C
/* AaSysCom Message Envelope Format (MEF) read mask  */
#define AASYSCOM_MEF_READ_MASK      0x0003
/* AaSysCom Sic v1 header defs */
#define AASYSCOM_CLEAR_APF          0xFFF3
#define AASYSCOM_SET_APF_LITTLE8    (EAaSysComMsgApf_8Little << 2)
#define AASYSCOM_SET_APF(A)         CCS_STATIC_CAST(u16,(A << 2))

/* AaSysCom header flags field best effort option value */
#ifndef UF_BEST_EFFORT_TRANSPORT
#define UF_BEST_EFFORT_TRANSPORT 0x10
#endif

#define AASYSCOM_EXTFLAGS_PRIORITY_READ_MASK       (0x0C00)
#define AASYSCOM_EXTFLAGS_CLEAR_PRIORITY           CCS_STATIC_CAST(u16,(~AASYSCOM_EXTFLAGS_PRIORITY_READ_MASK))
#define AASYSCOM_EXTFLAGS_SET_PRIORITY_UNSPECIFIED (EAaSysComMsgPriority_Unspecified << 10)
#define AASYSCOM_EXTFLAGS_SET_PRIORITY_LOW         (EAaSysComMsgPriority_Low << 10)
#define AASYSCOM_EXTFLAGS_SET_PRIORITY_MEDIUM      (EAaSysComMsgPriority_Medium << 10)
#define AASYSCOM_EXTFLAGS_SET_PRIORITY_HIGH        (EAaSysComMsgPriority_High << 10)
#define AASYSCOM_EXTFLAGS_SET_PRIORITY(A)          CCS_STATIC_CAST(u16,((A) << 10))
#define AASYSCOM_EXTFLAGS_GET_PRIORITY(A)          CCS_STATIC_CAST(u16,(((A) & AASYSCOM_EXTFLAGS_PRIORITY_READ_MASK) >> 10))
#define AASYSCOM_EXTFLAGS_DSCP_READ_MASK           (0x0FC0)
#define AASYSCOM_EXTFLAGS_DSCP_CLEAR_MASK          CCS_STATIC_CAST(u16,(~AASYSCOM_EXTFLAGS_DSCP_READ_MASK))
#define AASYSCOM_EXTFLAGS_SET_DSCP(A)              CCS_STATIC_CAST(u16,((A) << 6))
#define AASYSCOM_EXTFLAGS_GET_DSCP(A)              CCS_STATIC_CAST(u16,(((A) & AASYSCOM_EXTFLAGS_DSCP_READ_MASK) >> 6))
#define AASYSCOM_EXTFLAGS_DSCP_VALID_READ_MASK     (0x0020)
#define AASYSCOM_EXTFLAGS_DSCP_VALID_CLEAR_MASK    CCS_STATIC_CAST(u16,(~AASYSCOM_EXTFLAGS_DSCP_VALID_READ_MASK))
#define AASYSCOM_EXTFLAGS_GET_DSCP_VALID(A)        CCS_STATIC_CAST(u16,(((A) & AASYSCOM_EXTFLAGS_DSCP_VALID_READ_MASK) >> 5))

/* Structure definitions for little endian targets. */
#ifdef CCS_LITTLE_ENDIAN

/* Internal message header (SICv1). */
typedef struct SInternalMsgHeader
{
  TAaSysComMsgId   msgId;    /**< do not use directly */
  u16              extflags; /**< do not use directly\n
                                  Extended flags:\n
                                  xxxx0000 00000000 - message version:\n
                                  0000              - NMAP-compilance/SICv1\n
                                  other values      - reserved\n
                                  \n
                                  If DSCP bit is not set:\n
                                  0000xx00 00000000 - message priority\n
                                      00            - priority is unspecified\n
                                      01            - priority is low\n
                                      10            - priority is medium\n
                                      11            - priority is high\n
                                  000000xx xx000000 - not used\n
                                        xx xx       - not used\n
                                  If DSCP bit is set:\n
                                  0000xxxx xx100000 - DSCP\n
                                      xxxx xx       - DSCP value\n
                                  \n
                                  00000000 00x00000 - DSCP valid\n
                                             0      - DSCP is not used\n
                                             1      - DSCP is used\n
                                  00000000 0000x000 - delivery order bit\n
                                               0    - in order delivery not active\n
                                               1    - in order delivery active */
  TAaSysComSicad   target;   /**< do not use directly */
  TAaSysComSicad   sender;   /**< do not use directly */
  u16              flags;    /**< do not use directly\n
                                  System flags:\n
                                  x0000000 00000000 - reserved (not used any more: SF_RELIABLE_ACK_REQUIRED (RTM)):\n
                                  0                 - acknowledgement is not required\n
                                  1                 - acknowledgement is required\n
                                  0x000000 00000000 - SF_RELIABLE_FWD (RTM):\n
                                   0                - real-time message is not going between RTM nodes\n
                                   1                - real-time message is going between RTM nodes (RTM)\n
                                  00x00000 00000000 - SF_RESYNCH (RTM):\n
                                    0               - sequence number doesn't need to be resynchronized\n
                                    1               - sequence number needs to be resynchronized\n
                                  000x0000 00000000 - SF_MONITORED:\n
                                     0              - message was not tracked\n
                                     1              - message has already been tracked\n
                                  0000xxxx 00000000 - SF_SEQ_NUM_MASK (RTM):\n
                                      xxxx          - sequence number\n
                                  User flags:\n
                                  00000000 x0000000 - UF_RELIABLE_TRANSFER (RTM):\n
                                           0        - non-reliable transfer mode\n
                                           1        - reliable transfer mode\n
                                  00000000 0x000000 - UF_RELIABLE_RT (RTM):\n
                                            0       - Non-real-time message\n
                                            1       - Real-time message (RTM)\n
                                  00000000 00x00000 - MAPC:\n
                                             0      - payload part is not compressed\n
                                             1      - payload part is compressed\n
                                  00000000 000x0000 - UF_BEST_EFFORT_TRANSPORT:\n
                                              0     - reliable transfer mode\n
                                              1     - non-reliable transfer mode / best effort\n
                                  00000000 0000xx00 - MAPF:\n
                                               00   - 32bit word / big endian\n
                                               01   - 32bit word / little endian\n
                                               10   - 8bit word / big endian\n
                                               11   - 8bit word / little endian\n
                                  00000000 000000xx - MEF:\n
                                                 00 - NMAP\n
                                                 01 - reserved\n
                                                 10 - reserved\n
                                                 11 - SICv1 with trailer */
  TAaSysComMsgSize msgSize;  /**< do not use directly */
} SInternalMsgHeader;

/* SIC v1 trailer */
typedef struct SInternalMsgTrailer
{
  u32       spare;    /**< do not use directly */
  u8        flags;    /**< do not use directly */
  u8        reserved; /**< do not use directly */
  u16       crc;      /**< do not use directly */
} SInternalMsgTrailer;

/* SIC address. */
typedef struct SSicAddress
{
  TAaSysComCpid   cpId; /**< do not use directly */
  TAaSysComNid    nId;  /**< do not use directly */
} SSicAddress;


/* SIC header flags. */
typedef struct SSicHeaderFlags
{
  u8 user;       /**< Reserved for application layer, transported "as is".*/
  u8 system;     /**< Reserved for transportation/platform layer (checksum
                    etc). */
}SSicHeaderFlags;


#else

/* Structure definitions for big endian targets. */
/* Internal message header (SICv1). */
typedef struct SInternalMsgHeader
{
  u16              extflags; /**< do not use directly\n
                                  Extended flags:\n
                                  xxxx0000 00000000 - message version:\n
                                  0000              - NMAP-compilance/SICv1\n
                                  other values      - reserved\n
                                  \n
                                  If DSCP bit is not set:\n
                                  0000xx00 00000000 - message priority\n
                                      00            - priority is unspecified\n
                                      01            - priority is low\n
                                      10            - priority is medium\n
                                      11            - priority is high\n
                                  000000xx xx000000 - not used\n
                                        xx xx       - not used\n
                                  If DSCP bit is set:\n
                                  0000xxxx xx100000 - DSCP\n
                                      xxxx xx       - DSCP value\n
                                  \n
                                  00000000 00x00000 - DSCP valid\n
                                             0      - DSCP is not used\n
                                             1      - DSCP is used\n
                                  00000000 0000x000 - delivery order bit\n
                                               0    - in order delivery not active\n
                                               1    - in order delivery active */
  TAaSysComMsgId   msgId;    /**< do not use directly */
  TAaSysComSicad   target;   /**< do not use directly */
  TAaSysComSicad   sender;   /**< do not use directly */
  TAaSysComMsgSize msgSize;  /**< do not use directly */
  u16              flags;    /**< do not use directly\n
                                  System flags:\n
                                  x0000000 00000000 - reserved (not used any more: SF_RELIABLE_ACK_REQUIRED (RTM)):\n
                                  0                 - acknowledgement is not required\n
                                  1                 - acknowledgement is required\n
                                  0x000000 00000000 - SF_RELIABLE_FWD (RTM):\n
                                   0                - real-time message is not going between RTM nodes\n
                                   1                - real-time message is going between RTM nodes (RTM)\n
                                  00x00000 00000000 - SF_RESYNCH (RTM):\n
                                    0               - sequence number doesn't need to be resynchronized\n
                                    1               - sequence number needs to be resynchronized\n
                                  000x0000 00000000 - SF_MONITORED:\n
                                     0              - message was not tracked\n
                                     1              - message has already been tracked\n
                                  0000xxxx 00000000 - SF_SEQ_NUM_MASK (RTM):\n
                                      xxxx          - sequence number\n
                                  User flags:\n
                                  00000000 x0000000 - UF_RELIABLE_TRANSFER (RTM):\n
                                           0        - non-reliable transfer mode\n
                                           1        - reliable transfer mode\n
                                  00000000 0x000000 - UF_RELIABLE_RT (RTM):\n
                                            0       - Non-real-time message\n
                                            1       - Real-time message (RTM)\n
                                  00000000 00x00000 - MAPC:\n
                                             0      - payload part is not compressed\n
                                             1      - payload part is compressed\n
                                  00000000 000x0000 - UF_BEST_EFFORT_TRANSPORT:\n
                                              0     - reliable transfer mode\n
                                              1     - non-reliable transfer mode / best effort\n
                                  00000000 0000xx00 - MAPF:\n
                                               00   - 32bit word / big endian\n
                                               01   - 32bit word / little endian\n
                                               10   - 8bit word / big endian\n
                                               11   - 8bit word / little endian\n
                                  00000000 000000xx - MEF:\n
                                                 00 - NMAP\n
                                                 01 - reserved\n
                                                 10 - reserved\n
                                                 11 - SICv1 with trailer */
} SInternalMsgHeader;

/* SIC v1 trailer */
typedef struct SInternalMsgTrailer
{
  u32       spare;    /**< do not use directly */
  u16       crc;      /**< do not use directly */
  u8        reserved; /**< do not use directly */
  u8        flags;    /**< do not use directly */
} SInternalMsgTrailer;  /**< do not use directly */

/* SIC address. */
typedef struct SSicAddress
{
  TAaSysComNid   nId;  /**< do not use directly */
  TAaSysComCpid  cpId; /**< do not use directly */
} SSicAddress;




/* SIC header flags. */
typedef struct SSicHeaderFlags
{
  u8 system;     /**< Reserved for transportation/platform layer (checksum
                    etc). */
  u8 user;       /**< Reserved for application layer, transported "as is". */
}SSicHeaderFlags;

#endif /* CCS_LITTLE_ENDIAN */

/* SIC message. */
typedef struct SMsgData
{
  SInternalMsgHeader header;   /**< do not use directly */
  u32                userData; /**< do not use directly */
} SMsgData;

/* @} end: @name Structure definitions */

/*@} end: addtogroup dgAaSysComCommon AaSysCom Common*/

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOM_DEFS_H */
