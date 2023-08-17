/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2017 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AACONFIG_TAG_DEF_H_
#define _MCU_IF_AACONFIG_TAG_DEF_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../../COMMON/Definitions/IfAaConfigTag_Defs.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaConfigTag_Defs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagDefsMcu AaConfigTag MCU definitions
 * @ingroup dgAaConfigTagDefs
 */
/*@{*/

/** @brief The tag defines if CC&S is running in RAT container.
    The type of tag is u32. Value 1 indicates CC&S running inside RAT container.*/
#define   AACONFIG_TAG_CCS_RAT_MODE_ENABLED "sys.ccs.rat.mode.enabled"

/** The tag indicates persistent file system mounted in read-only mode.
 *  The type of tag is u32.
 *  Value 1 indicates persistent file system mounted is read-only mode. */
#define   AACONFIG_TAG_NAME_PERSISTENT_READ_ONLY "sys.fs.persistent.read.only"

/** @brief Attribute tag change mode */
typedef enum EAaConfigTagChangeMode
{
  EAaConfigTagChangeMode_Invalid,    /**< Invalid change mode */
  EAaConfigTagChangeMode_Private,    /**< Private change mode */
  EAaConfigTagChangeMode_Public,     /**< Public change mode */
  EAaConfigTagChangeMode_Persistent  /**< Persistent change mode */
} EAaConfigTagChangeMode;

/**
 * @brief Attribute tag value union
 */
typedef union UAaConfigTagValue
{
  u16 u16Value;                                    /**< u16 attribute tag value */
  u32 u32Value;                                    /**< u32 attribute tag value */
  char stringValue[AACONFIG_TAG_MAX_DATA_LENGTH];  /**< String attribute tag value */
  u8 anyValue[AACONFIG_TAG_MAX_DATA_LENGTH];       /**< Any data attribute tag value */
} UAaConfigTagValue;

/**
 * @brief Attribute tag data structure
 */
typedef struct SAaConfigTagData
{
  char name[AACONFIG_TAG_MAX_NAME_LENGTH];  /**< Attribute tag name */
  EAttributeType type;                      /**< Attribute tag type */
  u32 size;                                 /**< Attribute tag value size */
  UAaConfigTagValue value;                  /**< Attribute tag value */
} SAaConfigTagData;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AACONFIG_TAG_DEF_H_
