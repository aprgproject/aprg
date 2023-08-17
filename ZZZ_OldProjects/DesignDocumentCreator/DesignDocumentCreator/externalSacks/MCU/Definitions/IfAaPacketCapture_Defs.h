/** @file
*   @brief Definitions of AaPacketCapture.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2018 Nokia. All rights reserved.$
*/

#ifndef IF_MCU_AAPACKETCAPTURE_DEFS_H
#define IF_MCU_AAPACKETCAPTURE_DEFS_H

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaPacketCapture AaPacketCapture MCU
 * @ingroup dgAaPacketCapture
 *
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/** @name Interface types (MCU specific)
 * @{
 */

/**
 * @brief   Indicates if service is enabled:
 *          - 0 - disabled;
 *          - 1 - enabled.
 *          By default, service is disabled.
 */
#define AAPACKETCAPTURE_CONFIG_TAG_SERVICE_ENABLED      "ccs.service.aapacketcapture.service_enabled"

/**
 * @brief   The location of the dump file with captured packets.
 *          If not set, default location will be used ("/ram/").
 */
#define AAPACKETCAPTURE_CONFIG_TAG_DUMP_FILE_LOCATION   "ccs.service.aapacketcapture.dump_file.location"

/**
 * @brief   Network traffic capture status.
 */
typedef enum EAaPacketCaptureStatus
{
    EAaPacketCaptureStatus_Ok                       = 0,    /**< Successfully performed operation. */
    EAaPacketCaptureStatus_StartSuccess             = 1,    /**< Successfully started packets capturing. */
    EAaPacketCaptureStatus_CaptureSuccess           = 2,    /**< Successfully captured packets. */
    EAaPacketCaptureStatus_CaptureFailure           = 3,    /**< Failed to capture packets. */
    EAaPacketCaptureStatus_InitializationFailure    = 4,    /**< Initialization failure. */
    EAaPacketCaptureStatus_PcapCreateFailed         = 5,    /**< Failed to create live capture handle. */
    EAaPacketCaptureStatus_ApplyFilterFailed        = 6,    /**< Failed to apply filter. */
    EAaPacketCaptureStatus_DumpFileOpenFailed       = 7,    /**< Failed to open dump file. */
    EAaPacketCaptureStatus_StatsCollectionFailed    = 8,    /**< Failed to collect dump statistics. */
    EAaPacketCaptureStatus_UnknownCaptureId         = 9,    /**< Unknown capture id. */
    EAaPacketCaptureStatus_OperationNotSupported    = 10,   /**< Operation is not supported. */
    EAaPacketCaptureStatus_Undefined                = 11,   /**< Undefined issue occurred. */
    EAaPacketCaptureStatus_ConnectionInProgress     = 12,   /**< Connection to remote sink is in progress. */
    EAaPacketCaptureStatus_SocketCreationFailed     = 13,   /**< Failed to create socket. */
    EAaPacketCaptureStatus_BadAddress               = 14,   /**< Bad ip address. */
    EAaPacketCaptureStatus_ConnectionFailed         = 15,   /**< Connection to remote sink failed. */
    EAaPacketCaptureStatus_StreamOpenFailed         = 16,   /**< Failed to open stream for socket. */
    EAaPacketCaptureStatus_DumpStreamOpenFailed     = 17    /**< Failed to open dump stream. */
} EAaPacketCaptureStatus;

/**
 * @brief   Stop conditions of packets capturing.
 *
 *          Packets capturing will be stopped as soon as
 *          the first stop condition is being met.
 *          Value 0 means that condition will be ignored.
 */
typedef struct
{
    i32 numOfPacketsToCapture;  /**< Number of packets to capture. */
    i32 captureFileSizeBytes;   /**< The limit of the dump file in bytes. */
    u32 captureTimeSec;         /**< The time to capture packets in seconds. */
} SAaPacketCaptureStopConditions;

/**
 * @brief   The statistics of packets capturing.
 */
typedef struct
{
    u64 received;           /**< The amount of received packets. */
    u64 dropped;            /**< The amount of dropped packets, because
                                 there was no room in the operating system's
                                 buffer when they arrived as packets were not
                                 being read fast enough. */
    u64 interfaceDropped;   /**< The amount of dropped packets by network interface
                                 or it's driver (not supported on all platforms) */
} SAaPacketCaptureStatistics;

/**
 * @brief   AaPacketCapture's protocol.
 */
typedef enum EAaPacketCaptureProtocol
{
    EAaPacketCaptureProtocol_SCTP   = 0,    /**< SCTP protocol. */
    EAaPacketCaptureProtocol_TCP    = 1,    /**< TCP protocol. */
    EAaPacketCaptureProtocol_UDP    = 2,    /**< UDP protocol. */
    EAaPacketCaptureProtocol_UDPCP  = 3     /**< UDPCP protocol. */
} EAaPacketCaptureProtocol;

/**
 * @brief   Callback called after completing packets capturing process
 *          in order to notify the user of capture result.
 *
 * @param[in]   captureId           The id of packet capturing.
 * @param[in]   status              Status of packet capture process:
 *                                  - success: EAaPacketCaptureStatus_CaptureSuccess;
 *                                  - failure: Proper status from EAaPacketCaptureStatus.
 * @param[in]   captureStatistics   The statistics of packets capture process.
 */
typedef void(*AaPacketCaptureResultCallback)(u32 captureId,
        EAaPacketCaptureStatus status,
        SAaPacketCaptureStatistics captureStatistics);

/** @} */

/** @} end: @addtogroup dgAaPacketCapture AaPacketCapture MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AAPACKETCAPTURE_DEFS_H */
