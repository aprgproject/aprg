/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_RAD_DEF_H_
#define _COMMON_IF_AACONFIG_RAD_DEF_H_

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigRadDefs AaConfigRad definitions
 * @ingroup dgAaConfigRad
 */

/**
 * @defgroup dgAaConfigRadDefsCommon AaConfigRad common definitions
 * @ingroup dgAaConfigRadDefs
 */
/*@{*/

/** @brief Indicates that all R&D parameters from a domain are requested */
#define AACONFIG_RAD_PARAMS_ALL  0

/** @brief R&D Master CPID */
#define AACONFIG_STATIC_RAD_MASTER_TASK         0x0606
/** @brief R&D Master CPID */
#define AACONFIG_STATIC_RAD_MASTER_CPID         AACONFIG_STATIC_RAD_MASTER_TASK
/** @brief R&D first Slave CPID */
#define AACONFIG_RAD_SLAVE_CPID                 0x060C
/** @brief AaConfig R&D service to configure tags */
#define AACONFIG_CONFIGURE_SERVICE_CPID         0x0616

/** @brief RadSlave address */
#define AACONFIG_RAD_SLAVE_ADDR                 "ccs.service.aaconfig.rad.slave.addr"
/** @brief RadSlave static cpid */
#define AACONFIG_RAD_SLAVE_STATIC_CPID          "ccs.service.aaconfig.rad.slave.cpid" /* probably not used */
/** @brief RadMaster online */
#define AACONFIG_TAG_RADMASTER_ONLINE         "ccs.service.aaconfig.rad.master.online"
/** @brief Location (full path) to the configuration file */
#define   AACONFIGRAD_TAG_FILE_LOCATION          "ccs.service.aaconfig.rad.file.location"
/** @brief Location (full path) to the oneshot configuration file */
#define   AACONFIGRAD_TAG_ONE_FILE_LOCATION      "ccs.service.aaconfig.rad.one.file.location"
/** @brief Location (full path) to the RAD slave local configuration file */
#define   AACONFIGRAD_TAG_LOCAL_FILE_LOCATION    "ccs.service.aaconfig.rad.local.file.location"
/** @brief Location (full path) to the RAD slave oneshot local configuration file */
#define   AACONFIGRAD_TAG_LOCAL_ONE_FILE_LOCATION    "ccs.service.aaconfig.rad.local.one.file.location"
/** @brief AaConfig has written new parameters to file */
#define   AACONFIGRAD_TAG_FILE_READY             "ccs.service.aaconfig.rad.file.ready"
/** @brief Disables starting of AaConfigRadMaster.

This tag must be set BEFORE Ce level startup, because this only prevents master to be started, does not
kill master if it is already running. Type of tag is TBoolean with value GLO_TRUE meaning that master startup is disabled. */
#define   AACONFIGRAD_TAG_MASTER_DISABLED        "ccs.service.aaconfig.rad.master.disabled"
/** @brief DOMAIN_PREFIX and POSTFIX are used to compose the attribute tag which is set 1 when API
   AaConfigRadRegisterDomainSynch() is used for Domain registration. The tag
   PREFIX<Domain-ID>POSTFIX is set after parameter negotiation with RadMaster has finished. */
#define   AACONFIG_TAG_SYNCH_DOMAIN_PREFIX      "ccs.service.aaconfig.rad.domain."
/** @brief See AACONFIG_TAG_SYNCH_DOMAIN_PREFIX */
#define   AACONFIG_TAG_SYNCH_DOMAIN_POSTFIX     ".synched"

/** @brief Maximum number of R&D tags in R&D SW domain */
#define AACONFIG_RAD_DOMAIN_MAX_TAG_COUNT 2500


/** @brief AaConfig R&D parameter operating mode selector */
typedef enum EAaConfigRadOperatingMode {
  EAaConfigRadOperatingMode_Master = 1, /**< R&D Master has access */
  EAaConfigRadOperatingMode_Slave       /**< R&D Slave has access */
} EAaConfigRadOperatingMode;

/** @brief AaConfig R&D parameter setting type selector */
typedef enum EAaConfigRadSettingType
{
  EAaConfigRadSettingType_Factory             = 0, /**< Factory defaults, currently same as "FactoryAllDomains" */
  EAaConfigRadSettingType_Dynamic             = 1, /**< Change dynamic values */
  EAaConfigRadSettingType_Persistent          = 2, /**< Write values to file */
  EAaConfigRadSettingType_FactoryAllDomains      = 3, /**< Factory defaults, all domains */
  EAaConfigRadSettingType_PersistentOverOneReset = 4  /**< BASE0017_08: write values to OneReset file */
} EAaConfigRadSettingType;

/** @brief AaConfig R&D parameters setting variant selector */
typedef enum EAaConfigRadSetVariant
{
  EAaConfigRadSetVariant_Invalid       = 0, /**< Invalid selector */
  EAaConfigRadSetVariant_Actual        = 1, /**< Set actual, given value */
  EAaConfigRadSetVariant_Factory       = 2, /**< Restores values to factory defaults */
  EAaConfigRadSetVariant_FactoryDomain = 3, /**< Restores domain all values to factory defaults */
  EAaConfigRadSetVariant_FactoryAll    = 4  /**< Restore all domains all values to factory defaults */
} EAaConfigRadSetVariant;

/** @brief AaConfig R&D parameters setting mask */
typedef enum EAaConfigRadParamSetMask
{
  EAaConfigRadParamSetMask_Invalid                     = 0x0, /**< Invalid mask */
  EAaConfigRadParamSetMask_Current                     = 0x1, /**< Setting is applied immediately and valid until reset */
  EAaConfigRadParamSetMask_OneReset                    = 0x2, /**< Setting survives single reset */
  EAaConfigRadParamSetMask_Current_OneReset            =      /**< Setting is applied immediately and survives single reset */
    (EAaConfigRadParamSetMask_Current |
    EAaConfigRadParamSetMask_OneReset),
  EAaConfigRadParamSetMask_Persistent                  = 0x4, /**< Setting is persistent */
  EAaConfigRadParamSetMask_Current_Persistent          =      /**< Setting is applied immediately and persistent */
    (EAaConfigRadParamSetMask_Current |
    EAaConfigRadParamSetMask_Persistent),
  EAaConfigRadParamSetMask_OneReset_Persistent         =      /**< Setting is one reset resistant and persistent */
    (EAaConfigRadParamSetMask_OneReset |
    EAaConfigRadParamSetMask_Persistent),
  EAaConfigRadParamSetMask_Current_OneReset_Persistent =      /**< Setting is applied immediately,one reset resistant and persistent */
    (EAaConfigRadParamSetMask_Current |
    EAaConfigRadParamSetMask_OneReset |
    EAaConfigRadParamSetMask_Persistent)
} EAaConfigRadParamSetMask;

/** @brief AaConfig R&D parameters setting scope selector */
typedef enum EAaConfigRadSetScope
{
  EAaConfigRadSetScope_Invalid = 0,  /**< Invalid selector */
  EAaConfigRadSetScope_Local   = 1,  /**< Local node selector */
  EAaConfigRadSetScope_Global  = 2   /**< All nodes selector */
} EAaConfigRadSetScope;

/** @brief AaConfig R&D parameter status */
typedef enum EAaConfigRadParamStatus
{
  EAaConfigRadParamStatus_Ok             = 0,
  EAaConfigRadParamStatus_OutOfRange     = 1,
  EAaConfigRadParamStatus_Timeout        = 2,
  EAaConfigRadParamStatus_Error          = 3
} EAaConfigRadParamStatus;

/** @brief AaConfig R&D registration status */
typedef enum EAaConfigRadRegistrationStatus
{
  EAaConfigRadRegistrationStatus_Ok       = 0,
  EAaConfigRadtRegistrationStatus_Failed  = 1
}EAaConfigRadRegistrationStatus;

/** @brief R&D parameter */
typedef struct SAaConfigRadParams
{
  u32      index;                                  /**< index of R&D parameter */
  u32      size;                                   /**< size of R&D parameter */
  u32      value;                                  /**< value of R&D parameter */
} SAaConfigRadParams;

/**
********************************************************************************
*
* @brief        Observer callback function typedef for R&D flag changes.
* @param[in]    flag    R&D flag number.
* @param[in]    value   value or R&D flag.
*
*******************************************************************************/
typedef void TAaConfigRadObserver(const u32 flag,
                                  const u32 value);

/*!
 *  @brief  Type of function pointer for initialize domain factory defaults.
 */
typedef void (*InitializeParametersPtr)(void);

/*!
 *  @brief  Type of R&D domain object.
 */
typedef struct SRadDomain
{
  const char*   namePtr; /**< Name of domain. */
  InitializeParametersPtr   initializeParameters; /**< Function for initialize domain factory defaults. */
  u32           tagCount; /**< Keeps count of domain tags. */
  u32*          valueTable; /**< Table which stores all domain R&D tag values. */
  u32*          defaultValueTable; /**< Table which stores all default R&D tag values. */
  const char**  nameTable; /**< Table which stores all domain R&D tag names. */

}SRadDomain;

/** @brief AaConfig R&D parameter data */
typedef struct SAaConfigRadParamData
{
  u32                        index;                /**< R&D parameter index */
  u32                        defaultValue;         /**< R&D parameter default value */
  u32                        currentValue;         /**< R&D parameter current value */
  u32                        oneResetValue;        /**< R&D parameter one reset persistent storage value */
  u32                        persistentValue;      /**< R&D parameter persistent storage value */
  EAaConfigRadParamSetMask   validMask;            /**< R&D parameter values validation mask, defines which values are set and valid*/
} SAaConfigRadParamData;
/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_RAD_DEF_H_
