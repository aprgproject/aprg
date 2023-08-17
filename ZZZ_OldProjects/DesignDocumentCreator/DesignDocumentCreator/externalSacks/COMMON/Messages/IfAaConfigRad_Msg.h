/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_RAD_MSG_H_
#define _COMMON_IF_AACONFIG_RAD_MSG_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>
#include <ERadSwDomain.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfigRad_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigRadMsg AaConfigRad messages
 * @ingroup dgAaConfigRad
 */

/**
 * @defgroup dgAaConfigRadMsgCommon AaConfigRad common messages
 * @ingroup dgAaConfigRadMsg
 */

/**
 * @defgroup dgAaConfigRadMsgCommonExt AaConfigRad common external messages
 * @ingroup  dgAaConfigRadMsgCommon
 */
/*@{*/

/** Inform application about changed R&D parameter value */
#define AACONFIG_RAD_CHANGE_NOTIF_MSG           0x08D1      /* !- SIGNO(struct SAaConfigRadChangeNotif) -!  */
/** Inform application about updated R&D parameter value(s) of domain */
#define AACONFIG_RAD_UPDATE_NOTIF_MSG           0x1B90      /* !- SIGNO(struct SAaConfigRadUpdateNotif) -!  */

/*@}*/

/**
* @defgroup dgAaConfigRadMsgCommonInt AaConfigRad common internal messages
* @ingroup  dgAaConfigRadMsgCommon
*
* These messages are available for CC&S internal users.
*
*/
/*@{*/

/** Master indication */
#define AACONFIG_RAD_MASTER_IND_MSG             0x08CF      /* !- SIGNO(struct void) -! */
/** Asynchronous domain registration indication */
#define AACONFIG_RAD_DOMAIN_REGISTER_IND_MSG    0x08D0      /* !- SIGNO(struct AaConfig_RadDomainRegisterInd) -!  */
/** Master indication */
#define AACONFIG_RAD_MASTER_IND_REQ_MSG         0x0971      /* !- SIGNO(struct void) -! */
/** Set R&D parameter request */
#define AACONFIG_RAD_SET_PARAMS_REQ_MSG         0x2011      /* !- SIGNO(struct SAaConfigSetRadParamsReq) -!  */
/** Set R&D parameter response */
#define AACONFIG_RAD_SET_PARAMS_RESP_MSG        0x2012      /* !- SIGNO(struct SAaConfigSetRadParamsResp) -!  */
/** Get R&D parameter request */
#define AACONFIG_RAD_GET_PARAMS_REQ_MSG         0x2013      /* !- SIGNO(struct SAaConfigGetRadParamsReq) -!  */
/** Get R&D parameter response */
#define AACONFIG_RAD_GET_PARAMS_RESP_MSG        0x2014      /* !- SIGNO(struct SAaConfigGetRadParamsResp) -!  */
/** R&D parameters extended get request */
#define AACONFIG_RAD_PARAMS_EXT_GET_REQ_MSG     0x43DA      /* !- SIGNO(struct SAaConfigRadParamsExtGetReq) -!  */
/** R&D parameters extended get response */
#define AACONFIG_RAD_PARAMS_EXT_GET_RESP_MSG    0x43DB      /* !- SIGNO(struct SAaConfigRadParamsExtGetResp) -!  */
/** R&D parameter non-default get request */
#define AACONFIG_RAD_PARAMS_NON_DEFAULT_GET_REQ_MSG     0x43DC      /* !- SIGNO(struct SAaConfigRadParamsExtGetReq) -!  */
/** R&D parameter non-default get response */
#define AACONFIG_RAD_PARAMS_NON_DEFAULT_GET_RESP_MSG    0x43DD      /* !- SIGNO(struct SAaConfigRadParamsExtGetResp) -!  */
/** R&D parameters extended set request */
#define AACONFIG_RAD_PARAMS_EXT_SET_REQ_MSG     0x43DE      /* !- SIGNO(struct SAaConfigRadParamsExtSetReq) -!  */
/** R&D parameters extended set response */
#define AACONFIG_RAD_PARAMS_EXT_SET_RESP_MSG    0x43DF      /* !- SIGNO(struct SAaConfigRadParamsExtSetResp) -!  */
/** Set R&D parameter synchronize node request */
#define AACONFIG_RAD_SYNC_NODE_PARAMS_REQ_MSG           0x1B93      /* !- SIGNO(struct SAaConfigSetRadParamsReq) -!  */
/** Get R&D default parameter request */
#define AACONFIG_RAD_GET_DEFAULT_PARAMS_REQ_MSG         0x1B8C      /* !- SIGNO(struct SAaConfigGetRadDefaultParamsReq) -!  */
/** Get R&D default parameter response */
#define AACONFIG_RAD_GET_DEFAULT_PARAMS_RESP_MSG        0x1B8D      /* !- SIGNO(struct SAaConfigGetRadDefaultParamsResp) -!  */
/** Set master node id request */
#define AACONFIG_SET_MASTERNID_REQ_MSG          0x0ADB      /* !- SIGNO(struct SAaConfigSetMasternidReqMsg) -!  */
/** Set master node id response */
#define AACONFIG_SET_MASTERNID_RESP_MSG         0x0ADC      /* !- SIGNO(struct SAaConfigSetMasternidRespMsg) -! */
/** Synchronous domain registration request */
#define AACONFIG_RAD_DOMAIN_REGISTER_REQ_MSG    0x0BB2      /* !- SIGNO(struct AaConfig_RadDomainRegistrationReq) -!  */
/** Synchronous domain registration response */
#define AACONFIG_RAD_DOMAIN_REGISTER_RSP_MSG    0x0BB3      /* !- SIGNO(struct AaConfig_RadDomainRegistrationRsp) -!  */
/** Domain unregistration request */
#define AACONFIG_RAD_DOMAIN_UNREGISTER_REQ_MSG  0x1B94      /* !- SIGNO(struct AaConfig_RadDomainUnRegistrationReq) -!  */
/** Domain unregistration response */
#define AACONFIG_RAD_DOMAIN_UNREGISTER_RSP_MSG  0x1B95      /* !- SIGNO(struct AaConfig_RadDomainUnRegistrationRsp) -!  */
/** Get Domain registered request */
#define AACONFIG_RAD_GET_DOMAIN_REGISTERED_REQ_MSG  0x0C04      /* !- SIGNO(struct void) -!  */
/** Get Domain registered response */
#define AACONFIG_RAD_GET_DOMAIN_REGISTERED_RSP_MSG  0x0C05      /* !- SIGNO(struct SAaConfigGetMasterDomainRsp) -!  */

/*@}*/

/** @brief R&D parameter (default + current) */
typedef struct SAaConfigRadSyncParams
{
  u32      index;                                  /**< index of R&D parameter */
  u32      size;                                   /**< size of R&D parameter */
  u32      defValue;                               /**< value of R&D default parameter */
  u32      currValue;                              /**< value of R&D current parameter */
  TBoolean flashValid;                             /**< valid marker of R&D flash parameter */
  u32      flashValue;                             /**< value of R&D flash parameter */
} SAaConfigRadSyncParams;

/** @brief AaConfig R&D domain synchronous registration request message structure */
typedef struct AaConfig_RadDomainRegistrationReq{
  TAaSysComSicad                  requestor;              /**< SIC address */
  ERadSwDomain                    domain;                 /**< R&D sw domain */
  u32                             CcsVersion;             /**< CCS version number */
  u32                             ParameterCount;         /**< number of parameters */
  SAaConfigRadSyncParams          Parameter[1];           /**< R&D default, current + flash parameter */
}AaConfig_RadDomainRegistrationReq;

/** @brief AaConfig R&D domain synchronous registration response message structure */
typedef struct AaConfig_RadDomainRegistrationRsp{
  ERadSwDomain                          domain;           /**< R&D sw domain */
  EAaConfigRadRegistrationStatus        status;           /**< registration status */
  EAaConfigRadSettingType               settingType;      /**< R&D parameter setting type selector */
  u32                                   parameterCount;   /**< number of parameters */
  SAaConfigRadParams                    parameter[1];     /**< R&D parameter */
}AaConfig_RadDomainRegistrationRsp;

/** @brief AaConfig R&D domain synchronous unregistration request message structure */
typedef struct AaConfig_RadDomainUnRegistrationReq{
  TAaSysComSicad                  requestor;              /**< SIC address */
  ERadSwDomain                    domain;                 /**< R&D sw domain */
}AaConfig_RadDomainUnRegistrationReq;

/** @brief AaConfig R&D domain synchronous unregistration response message structure */
typedef struct AaConfig_RadDomainUnRegistrationRsp{
  ERadSwDomain                          domain;           /**< R&D sw domain */
  EAaConfigRadRegistrationStatus        status;           /**< registration status */
}AaConfig_RadDomainUnRegistrationRsp;

/** @brief AaConfig R&D parameter change notify message structure */
typedef struct SAaConfigRadChangeNotif
{
  u32       tag;    /**< R&D Tag Id */
  u32       value;  /**< New value */
} SAaConfigRadChangeNotif;

/** @brief AaConfig R&D domain update notify message structure */
typedef struct SAaConfigRadUpdateNotif
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
} SAaConfigRadUpdateNotif;


/** @brief Indication message of asynchronous registered domain */
typedef struct AaConfig_RadDomainRegisterInd
{
  u32                             domain;           /**< R&D sw domain */
  u32                             CcsVersion;       /**< CCS version number */
} AaConfig_RadDomainRegisterInd;

/** @brief Domain register structure. */
typedef struct SAaConfigMasterDomainReg
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  u32                             noOfSlaves;       /**< number of slave SICADs */
  TAaSysComSicad                  sicad[1];         /**< SIC address list */
} SAaConfigMasterDomainReg;

/** @brief Get master domain response message. */
typedef struct SAaConfigGetMasterDomainRsp
{
  u32                             noOfDomains;      /**< number of domains */
  SAaConfigMasterDomainReg        domainReg[1];     /**< R&D sw domain list */
} SAaConfigGetMasterDomainRsp;

/** @brief Set parameters request message. */
typedef struct SAaConfigSetRadParamsReq
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  EAaConfigRadSettingType         settingType;      /**< R&D parameter setting type selector */
  u32                             noOfParams;       /**< number of parameters */
  SAaConfigRadParams              params[1];        /**< R&D parameter */
} SAaConfigSetRadParamsReq;

/** @brief Set parameters response message. */
typedef struct SAaConfigSetRadParamsResp
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  EAaConfigRadParamStatus         paramState;       /**< R&D parameter status */
} SAaConfigSetRadParamsResp;

/** @brief Get parameters request message. */
typedef struct SAaConfigGetRadParamsReq
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
} SAaConfigGetRadParamsReq;

/** @brief Get parameters response message. */
typedef struct SAaConfigGetRadParamsResp
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  u32                             noOfParams;       /**< number of parameters */
  SAaConfigRadParams              params[1];        /**< R&D parameter */
} SAaConfigGetRadParamsResp;

/** @brief Get default parameters request message. */
typedef struct SAaConfigGetRadDefaultParamsReq
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
} SAaConfigGetRadDefaultParamsReq;

/** @brief Get default parameters response message. */
typedef struct SAaConfigGetRadDefaultParamsResp
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  u32                             noOfParams;       /**< number of parameters */
  SAaConfigRadParams              params[1];        /**< R&D parameter */
} SAaConfigGetRadDefaultParamsResp;

/** @brief AaConfig R&D parameters extended set request message */
typedef struct SAaConfigRadParamsExtSetReq
{
  EAaConfigRadSetVariant          variant;          /**< R&D parameters setting variant */
  EAaConfigRadParamSetMask        setMask;          /**< R&D parameters setting mask */
  EAaConfigRadSetScope            scope;            /**< R&D parameters setting scope selector */
  u32                             node;             /**< R&D parameters setting target nodes, valid only if scope is local */
  ERadSwDomain                    domain;           /**< R&D SW domain, valid only when variant is Actual, Factory or FactoryDomain */
  u32                             noOfParams;       /**< Number of parameters, valid only when variant is Actual or Factory */
  SAaConfigRadParams              params[1];        /**< R&D parameters, valid only when variant is Actual or Factory */
} SAaConfigRadParamsExtSetReq;

/** @brief AaConfig R&D parameters extended set response message. */
typedef struct SAaConfigRadParamsExtSetResp
{
  ERadSwDomain                    domain;           /**< R&D sw domain */
  EAaConfigRadParamStatus         paramState;       /**< R&D parameter set status */
} SAaConfigRadParamsExtSetResp;

/** @brief AaConfig R&D parameters extended get request */
typedef struct SAaConfigRadParamsExtGetReq
{
  EAaConfigRadSetScope            scope;            /**< Scope */
  u32                             node;             /**< Target node */
  ERadSwDomain                    domain;           /**< R&D SW domain */
  u32                             noOfParams;       /**< Number of requested parameters. If set to AACONFIG_RAD_PARAMS_ALL, all parameters from given domain are requested */
  u32                             params[1];        /**< Indexes of requested parameters. Relevant only if noOfParams value != AACONFIG_RAD_PARAMS_ALL */
} SAaConfigRadParamsExtGetReq;

/** @brief AaConfig R&D parameters extended get response */
typedef struct SAaConfigRadParamsExtGetResp
{
  ERadSwDomain                    domain;           /**< R&D SW domain */
  u32                             numnerOfParams;   /**< Number of R&D parameters */
  SAaConfigRadParamData           parameters[1];    /**< R&D parameters data */
} SAaConfigRadParamsExtGetResp;

/** @brief Set master-NID message. */
typedef struct SAaConfigSetMasternidReqMsg
{
  u32 masternid;                                    /**< master node ID */
}SAaConfigSetMasternidReqMsg;

/** @brief Set master-NID response message. */
typedef struct SAaConfigSetMasternidRespMsg
{
  u32 result;       /**< 0 ... masternid was set successfully, else error occurred */
  u32 masternid;    /**< new masternid, if set successfully (result == 0) */
}SAaConfigSetMasternidRespMsg;


#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_RAD_MSG_H_
