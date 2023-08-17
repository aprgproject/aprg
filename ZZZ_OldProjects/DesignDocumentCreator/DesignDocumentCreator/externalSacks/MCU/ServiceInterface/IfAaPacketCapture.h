/** @file
*   @brief Interfaces of AaPacketCapture.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2017 Nokia. All rights reserved.$
*/

#ifndef IF_MCU_AAPACKETCAPTURE_H
#define IF_MCU_AAPACKETCAPTURE_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <CcsCommon.h>
#include "../Definitions/IfAaPacketCapture_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaPacketCapture AaPacketCapture MCU
 * @ingroup dgAaPacketCapture
 *
 * Common Computer and Support SW Packet Capture.
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name AaPacketCapture (MCU specific)
 * @{
 */

/**
 * @brief   Start packets capturing with simple filter.
 *
 * @param[in]   interface   Interface on which packets are being captured.
 * @param[in]   port        Port on which packets are being captured.
 * @param[in]   protocol    Protocol that is being captured.
 * @param[in]   stop        Stop conditions that define the end of packets capturing.
 * @param[out]  callback    Callback used to communicate the status of the procedure.
 * @param[out]  captureId   The id of packet capturing.
 *
 * @return  Via return value:
 *          - success:  EAaPacketCaptureStatus_Ok (successfully triggered start).
 *          - failure:  EAaPacketCaptureStatus_InitializationFailure (initialization failure).
 *                      EAaPacketCaptureStatus_OperationNotSupported (operation not supported).
 *
 *          Via callback:
 *          - success: EAaPacketCaptureStatus_StartSuccess (successfully started);
 *          - failure: Proper status from EAaPacketCaptureStatus.
 *
 * @par Description:
 * Output file is automatically registered to snapshot with the following name:
 * - "sniffer_"     - prefix;
 * - device         - interface name, i.e. "lo";
 * - protocol       - protocol being captured, i.e. "udp";
 * - port           - port on which traffic is being captured, i.e. "16009";
 * - thread name    - the name of the thread that triggered capturing, i.e. "thr0";
 * - time           - time  of  starting  network  traffic  capture  procedure
 *                    (hours, minutes, seconds and milliseconds);
 * - ".pcap"        - file extension.
 *
 * The example of the dump file: sniffer_lo_udp_16009_thr0_11:22:33.444.pcap.
 *
 * All dump files are stored under /ram/aapacketcapture/ by default.
 * AAPACKETCAPTURE_CONFIG_TAG_DUMP_FILE_LOCATION configuration tag allows to change default directory.
 * Directory is being zipped (/ram/aapacketcapture.zip) and stored when snapshot is being created.
 * User shall look for files inside snapshot under aapacketcapture.zip.
 *
 * User does not have to pass callback if statuses are not needed.
 *
 * @par Usage:
 * The below example shows how API can be used:
 *
 * @code
 * const char *interface = "eth0";
 * u16 port = 16009;
 * EAaPacketCaptureProtocol protocol = EAaPacketCaptureProtocol_UDP;
 * SAaPacketCaptureStopConditions stop = {5, 0, 0};
 *
 * AaPacketCaptureStartWithSimpleFilter(interface, port, protocol, stop, nullptr);
 * @endcode
 */
EAaPacketCaptureStatus AaPacketCaptureStartWithSimpleFilter(
        const char *interface,
        u16 port,
        EAaPacketCaptureProtocol protocol,
        SAaPacketCaptureStopConditions stop,
        AaPacketCaptureResultCallback callback,
        u32 *captureId);

/**
 * @brief   Start packets capturing with complex (user defined) filter.
 *
 * @param[in]   interface   Interface on which packets are being captured.
 * @param[in]   filter      Filter used for packets capturing.
 * @param[in]   stop        Stop conditions that define the end of packets capturing.
 * @param[out]  callback    Callback used to communicate the status of the procedure.
 * @param[out]  captureId   The id of packet capturing.
 *
 * @return  Via return value:
 *          - success:  EAaPacketCaptureStatus_Ok (successfully triggered start).
 *          - failure:  EAaPacketCaptureStatus_InitializationFailure (initialization failure).
 *                      EAaPacketCaptureStatus_OperationNotSupported (operation not supported).
 *
 *          Via callback:
 *          - success: EAaPacketCaptureStatus_StartSuccess (successfully started);
 *          - failure: Proper status from EAaPacketCaptureStatus.
 *
 * @par Description:
 * Output file is automatically registered to snapshot with the following name:
 * - "sniffer_"     - prefix;
 * - device         - interface name, i.e. "lo";
 * - thread name    - the name of the thread that triggered capturing, i.e. "thr0";
 * - time           - time  of  starting  network  traffic  capture  procedure
 *                    (hours, minutes, seconds and milliseconds);
 * - ".pcap"        - file extension.
 *
 * The example of the dump file: sniffer_lo_thr0_11:22:33.444.pcap.
 *
 * All dump files are stored under /ram/aapacketcapture/ by default.
 * AAPACKETCAPTURE_CONFIG_TAG_DUMP_FILE_LOCATION configuration tag allows to change default directory.
 * Directory is being zipped (/ram/aapacketcapture.zip) and stored when snapshot is being created.
 * User shall look for files inside snapshot under aapacketcapture.zip.
 *
 * User does not have to pass callback if statuses are not needed.
 *
 * Filters are described in manual: http://www.tcpdump.org/manpages/pcap-filter.7.html
 *
 * @par Usage:
 * The below example shows how API can be used:
 *
 * @code
 * const char *interface = "eth0";
 * const char *filter = "dst host 127.0.0.1";
 * SAaPacketCaptureStopConditions stop = {5, 0, 0};
 *
 * AaPacketCaptureStartWithSimpleFilter(interface, port, protocol, stop, nullptr);
 * @endcode
 */
EAaPacketCaptureStatus AaPacketCaptureStartWithComplexFilter(
        const char *interface,
        const char *filter,
        SAaPacketCaptureStopConditions stop,
        AaPacketCaptureResultCallback callback,
        u32 *captureId);

/**
 * @brief   Stop packets capturing.
 *
 * @param[in] captureId The id of packet capturing.
 *
 * @return  Via return value:
 *          - success:  EAaPacketCaptureStatus_Ok (operation succeeded or already stopped/finished).
 *          - failure:  EAaPacketCaptureStatus_UnknownCaptureId in case of unknown capture id.
 *                      EAaPacketCaptureStatus_OperationNotSupported (operation not supported).
 *
 * @par Description:
 * Stopping network traffic capturing is not mandatory as it will finish
 * and clean-up once stop condition is being met.
 */
EAaPacketCaptureStatus AaPacketCaptureStop(u32 captureId);

/** @} */

/** @} end: @addtogroup dgAaPacketCapture AaPacketCapture MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AAPACKETCAPTURE_H */
