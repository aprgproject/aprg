/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_SVC_REG_MSG_H_
#define _COMMON_IF_AACONFIG_SVC_REG_MSG_H_

#include <CcsCommon.h>

#include <TAaSysComSicad.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfigSvcReg_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigSvcRegMsg AaConfigSvcReg messages
 * @ingroup dgAaConfigSvcReg
 */

/**
 * @defgroup dgAaConfigSvcRegMsgCommon AaConfigSvcReg common messages
 * @ingroup dgAaConfigSvcRegMsg
 */

/**
 * @defgroup dgAaConfigSvcRegMsgCommonExt AaConfigSvcReg common external messages
 * @ingroup  dgAaConfigSvcRegMsgCommon
 */
/*@{*/

/** Notify application about subscribed service */
#define AACONFIG_SVC_REG_NOTIF_MSG              0x1B9C      /* !- SIGNO(struct SAaConfigSvcRegistry) -!  */
/** Get service registry request */
#define AACONFIG_SVC_GET_SERVICE_REQ_MSG        0x1F24      /* !- SIGNO(struct SAaConfigLookupService) -!  */
/** Get service registry response */
#define AACONFIG_SVC_GET_SERVICE_RESP_MSG       0x1F25      /* !- SIGNO(struct SAaConfigSvcRegGetRspMsg) -!  */

/*@}*/

/**
 * @defgroup dgAaConfigSvcRegMsgCommonInt AaConfigSvcReg common internal messages
 * @ingroup  dgAaConfigSvcRegMsgCommon
 *
 * These messages are available for CC&S internal users.
 *
 */
/*@{*/

/** Service registry public register */
#define AACONFIG_SVC_REG_PUBLIC_REG_MSG         0x1B99      /* !- SIGNO(struct SAaConfigSvcRegistry) -!  */
/** Service registry public unregister */
#define AACONFIG_SVC_REG_PUBLIC_UNREG_MSG       0x1B9A      /* !- SIGNO(struct SAaConfigSvcRegistry) -!  */
/** Resend service registry publication request */
#define AACONFIG_SVC_REG_RESEND_PUBLIC_MSG      0x1B9B      /* !- SIGNO(struct void) -! */

/*@}*/

/** @brief AaConfig service registry get wildcard result list */
typedef struct SAaConfigSvcRegGetResService
{
  u32                         minor_version;       /**< minor version number of service */
  TAaSysComSicad              sicad;               /**< SIC address of service */
} SAaConfigSvcRegGetResService;

/** @brief AaConfig service registry get response list */
typedef struct SAaConfigSvcRegGetRes
{
  u32                            num_services;        /**< number of services */
  SAaConfigSvcRegGetResService   service[1];          /**< minor version + SIC address of service */
} SAaConfigSvcRegGetRes;

/** @brief AaConfig service registry get message struct */
typedef struct SAaConfigSvcRegGetRspMsg
{
  char  name[AACONFIG_SERVICE_MAX_NAME_LENGTH];       /**< name of service */
  u32                             major_version;      /**< major version number of service */
  u32                             minor_version;      /**< minor version number of service */
  EAaConfigSvcRegScope            scope;              /**< visibility of service */
  u32                             num_services;       /**< number of services */
  SAaConfigSvcRegGetResService    service[1];         /**< minor version + SIC address of service */
} SAaConfigSvcRegGetRspMsg;

/** @brief AaConfig service registry reverse lookup of service response list */
typedef struct SAaConfigLookupService
{
  char  name[AACONFIG_SERVICE_MAX_NAME_LENGTH];     /**< name of service */
  u32                             major_version;    /**< major version number of service */
  u32                             minor_version;    /**< minor version number of service */
  EAaConfigSvcRegScope            scope;            /**< visibility of service */
} SAaConfigLookupService;

/** @brief AaConfig service registry reverse lookup list */
typedef struct SAaConfigReverseLookupRes
{
  u32                             num_services;     /**< number of services */
  SAaConfigLookupService          service[1];       /**< service */
} SAaConfigReverseLookupRes;

/** @brief AaConfig service notify message structure */
typedef struct SAaConfigSvcRegistry
{
  char  name[AACONFIG_SERVICE_MAX_NAME_LENGTH];     /**< name of service */
  u32                             major_version;    /**< major version number of service */
  u32                             minor_version;    /**< minor version number of service */
  EAaConfigSvcRegScope            scope;            /**< visibility of service */
  TAaSysComSicad                  sicad;            /**< SIC address of service */
  u32                             eeId;             /**< EEId of service */
  TBoolean                        resend;           /**< resend indicator */
} SAaConfigSvcRegistry;

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_SVC_REG_MSG_H_
