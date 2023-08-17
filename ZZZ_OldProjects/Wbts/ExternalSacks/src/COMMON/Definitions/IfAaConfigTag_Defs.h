/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_TAG_DEF_H_
#define _COMMON_IF_AACONFIG_TAG_DEF_H_

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagDefs AaConfigTag definitions
 * @ingroup dgAaConfigTag
 */

/**
 * @defgroup dgAaConfigTagDefsCommon AaConfigTag common definitions
 * @ingroup dgAaConfigTagDefs
 */
/*@{*/

/** @brief Maximum length of attribute tag name */
#define AACONFIG_TAG_MAX_NAME_LENGTH 80

/** @brief Maximum length of attribute tag data */
#define AACONFIG_TAG_MAX_DATA_LENGTH 256

/** @brief AaConfig public tag store */
#define AACONFIG_TAG_MASTER_CPID                0x062B

/** @brief Tag value is set */
#define   AACONFIG_TAG_VALUE_TRUE               "TRUE"
/** @brief Tag value is not set */
#define   AACONFIG_TAG_VALUE_FALSE              "FALSE"

/** Ethernet interface 0 IPv4 address */
#define   AACONFIG_TAG_NAME_ETH0_IP             "sys.net.eth0.ip"
/** Ethernet interface 0 IPv4 alias 1 */
#define   AACONFIG_TAG_NAME_ETH0_IP1            "sys.net.eth0.ip1"
/** Ethernet interface 0 IPv6 address */
#define   AACONFIG_TAG_NAME_ETH0_IPV6           "sys.net.eth0.ipv6"
/** may be not used */
#define   AACONFIG_TAG_NAME_ETH0_ONLINE         "sys.net.eth0.online"
/** IP stack availability */
#define   AACONFIG_TAG_NAME_IP_STACK_ONLINE     "sys.net.stack.ip.online"
/** CE unit name */
#define   AACONFIG_TAG_NAME_CE_NAME             "sys.ce.name"
/** CE unit ID */
#define   AACONFIG_TAG_NAME_UNIT_ID             "sys.ce.unit"
/** CPU ID */
#define   AACONFIG_TAG_NAME_CPU_ID              "sys.ce.cpu"
/** may be not used */
#define   AACONFIG_TAG_NAME_BANNER              "sys.ce.banner"
/** Path of temporary file location */
#define   AACONFIG_TAG_NAME_TEMP_PATH           "sys.fs.temp.path"
/** Indicator that temporary file is up */
#define   AACONFIG_TAG_NAME_TEMP_ONLINE         "sys.fs.temp.online"
/** Path of persistent file location */
#define   AACONFIG_TAG_NAME_PERSISTENT_PATH     "sys.fs.persistent.path"
/** Indicator that persistent file is up */
#define   AACONFIG_TAG_NAME_PERSISTENT_ONLINE   "sys.fs.persistent.online"
/** Mount point for secure volume */
#define   AACONFIG_TAG_NAME_SECURE_MOUNT_POINT  "sys.fs.secure.mountpoint"
/** Volume name of secure volume */
#define   AACONFIG_TAG_NAME_SECURE_VOLUME       "sys.fs.secure.volume"
/** Mount point for /ffs/ volume */
#define   AACONFIG_TAG_NAME_FFS_PATH            "sys.fs.ffs.path"
/** Mount point for /ffs1/ volume */
#define   AACONFIG_TAG_NAME_FFS1_PATH           "sys.fs.ffs1.path"
/** Mount point for /ffs2/ volume */
#define   AACONFIG_TAG_NAME_FFS2_PATH           "sys.fs.ffs2.path"
/** Mount point for /ffs3/ volume */
#define   AACONFIG_TAG_NAME_FFS3_PATH           "sys.fs.ffs3.path"
/** Mount point for /ffs4/ volume */
#define   AACONFIG_TAG_NAME_FFS4_PATH           "sys.fs.ffs4.path"
/** Mount point for /rpram/ volume */
#define   AACONFIG_TAG_NAME_RPRAM_PATH          "sys.fs.rpram.path"
/** Indicator that reset-proof ram is up */
#define   AACONFIG_TAG_NAME_RESETPROOF_ONLINE   "sys.fs.resetproof.online"
/** Mount point for /logs/ volume */
#define   AACONFIG_TAG_NAME_LOGS_PATH           "sys.fs.logs.path"
/** Mount point for /raml/ volume */
#define   AACONFIG_TAG_NAME_RAML_PATH           "sys.fs.raml.path"
/** Size for /raml/ volume */
#define   AACONFIG_TAG_NAME_RAML_SIZE           "sys.fs.raml.size"
/** Mount point for /stb/ volume */
#define   AACONFIG_TAG_NAME_STB_PATH            "sys.fs.stb.path"
/** Mount point for /pns/ volume */
#define   AACONFIG_TAG_NAME_PNS_PATH            "sys.fs.pns.path"
/** Mount point for /data/ volume */
#define   AACONFIG_TAG_NAME_DATA_PATH           "sys.fs.data.path"
/** Indicator that HwapiExe is online */
#define   AACONFIG_TAG_HWAPI_ONLINE             "sys.hwapi.online"
/** Indicator that factory reset is set by Hwapi */
//#define   AACONFIG_TAG_FACTORY_RESET            "sys.factory.reset"
#define   AACONFIG_TAG_REPAIR_CENTER_RESET      "sys.repair.center.reset"
/** Indicator that configuration reset is active */
#define   AACONFIG_TAG_CONFIGURATION_RESET      "sys.configuration.reset"
/** Default nid value */
#define   AACONFIG_TAG_DEFAULT_NID              "sys.default.nodeid"
/** Parent node ID to current board */
#define   AACONFIG_TAG_PARENT_NID               "sys.parent.nodeid"
/** CCS Build version */
#define   AACONFIG_TAG_CCS_VERSION              "sys.ccs.version"
/** Indicator that CC&S CE startup is successful */
#define   AACONFIG_TAG_CCS_ONLINE               "sys.ccs.online"
/** Indicator that firmware update is ongoing.
 *  The tag semantics is following:
 *      - Tag is not set - No software update,
 *      - Tag is set to 0 - No software update,
 *      - Tag is set to 1 - 7 minute timeout,
 *      - Tag set to different value - the value defines timeout for software update given in seconds.
 */
#define   AACONFIG_TAG_FIRMWARE_UPDATE          "sys.firmware.update"
/** Indicator that the startup is after an ungraceful shutdown */
#define   AACONFIG_TAG_UNGRACEFUL_SHUTDOWN  "sys.recoverFromUngracefulShutdown"
/** Indicator that time and synchronization BASE2 model is enabled */
#define   AACONFIG_TAG_TIME_BASE_ENABLED        "sys.time.base.enabled"
/** @brief AaConfig has read configuration parameters at startup */
#define   AACONFIG_TAG_NAME_STARTUP_CONFIG_READY "ccs.service.aaconfig.startup.config.ready"
/** @brief Location (full path) to the configuration tag file */
#define   AACONFIG_PCF_FILE_LOCATION             "ccs.service.aaconfig.pcf.file.location"
/** @brief Location (OS path) to the configuration tag file */
#define   AACONFIG_OS_PCF_FILE_LOCATION          "ccs.service.aaconfig.os.pcf.file.location"
/** @brief AaConfigShell port number of the UDP port */
#define   AACONFIG_TAG_NAME_SHELL_DGRAM_PORT     "ccs.service.aaconfig.shell.dgram.port"
/** @brief AaConfigShell port number of the TCP port */
#define   AACONFIG_TAG_NAME_SHELL_STREAM_PORT    "ccs.service.aaconfig.shell.stream.port"


/** @brief AaConfig config tag types */
typedef enum EAttributeType
{
  invalid_type,
  u16_type,
  u32_type,
  string_type,
  any_type
} EAttributeType;

/**
********************************************************************************
*
* @brief        Observer callback function typedef.
* @param[in]    name    pointer to a tag name string.
* @param[in]    value   a pointer in which the value is stored.
* @param[in]    length  length of the value.
*
*******************************************************************************/
typedef void TAaConfigTagObserver(const char* const name,
                                  const void* const value,
                                  const u32 length);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_TAG_DEF_H_
