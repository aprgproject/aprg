/** @file
*   @brief AaTestPortServer MCU Definitions.
*
*   $Copyright: 2018, 2019 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AATESTPORTSERVER_DEF_H_
#define _MCU_IF_AATESTPORTSERVER_DEF_H_

#include <CcsCommon.h>
#include <glo_def.h>

/**
 * @defgroup dgAaTestPortServerMcuDefs AaTestPortServer MCU Definitions
 * @ingroup dgAaTestPortServer
 */

/*@{*/

/*!
 * Maximum length of AaTestPortServer name (with terminator).
 */
#define AATESTPORTSERVER_MAX_NAME_LENGTH    32

/*!
 * Minimum size, in bytes, of the server internal buffer.
 */
#define AATESTPORTSERVER_MIN_BUFFER_SIZE    131072

/*!
 * Maximum size, in bytes, of the server internal buffer.
 */
#define AATESTPORTSERVER_MAX_BUFFER_SIZE    5242880

/*!
 * Static cpid used by AaTestPortServer instance created during CE startup.
 */
#define AATESTPORTSERVER_CE_INSTANCE_CPID   0x662

/*!
 * Setting this config tag allows the user to set the AaTestPortServer internal buffer size.
 * The buffer size is restricted to range from #AATESTPORTSERVER_MIN_BUFFER_SIZE to
 * #AATESTPORTSERVER_MAX_BUFFER_SIZE (inclusive both sides).
 */
#define AATESTPORTSERVER_CONFIG_TAG_BUFFER_SIZE       "ccs.service.aatpserver.buffersize"

/*!
 * Setting this config tag allows the user to set the AaTestPortServer IP address in string format.
 * Only IPv6 IP family is supported. It is possible to pass IPv4 mapped to IPv6 if AaTestPortServer
 * should bind to IPv4 address.
 */
#define AATESTPORTSERVER_CONFIG_TAG_IP_ADDRESS        "ccs.service.testport.ipaddress"

/*!
 * The tag is used to start AaTestPortServer instance during CE startup.
 * The tag defines port that AaTestPortServer server will listen on.
 * The tag must be set before CE startup to have AaTestPortServer instance started.
 * The tag runtime modification has no effect.
 * If the tag is not set then AaTestPortServer instance will not be started.
 * The tag is u16 type.
 * The tag value must be greater than 0, as port 0 is treated by API as invalid parameter.
 */
#define AATESTPORTSERVER_CONFIG_TAG_CE_INSTANCE_PORT  "ccs.service.aatpserver.ce.instance.port"

/*!
 * Interface function return values.
 */
typedef enum EAaTPServerRetVal
{
    EAaTPServerRetVal_Ok,                 /*!< Success of action */
    EAaTPServerRetVal_Error,              /*!< Some internal error */
    EAaTPServerRetVal_InvalidParameter    /*!< Invalid parameter is given */
} EAaTPServerRetVal;

/*@}*/

#endif /* _MCU_IF_AATESTPORTSERVER_DEF_H_ */
