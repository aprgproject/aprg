/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaPostmortem shared definitions and types
* @module                AaPostMortem
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAPOSTMORTEM_DEFS_H
#define _MCU_RT_IFAAPOSTMORTEM_DEFS_H

#include <CcsCommon.h>

/**
*
* @defgroup dgAaPostmortemApiMcu MCU API
* @ingroup  dgAaPostmortem
**/
/*@{*/

#ifdef __cplusplus
extern "C"{
#endif

/*!
 *  A type for interface functions return value.
 */
typedef enum EAaPostmortemRetVal
{
    EAaPostmortemRetVal_Ok                   = 0, /*!< Success of action */
    EAaPostmortemRetVal_Error                = 1, /*!< Some internal error */
    EAaPostmortemRetVal_InvalidParameter     = 2, /*!< Invalid parameter is given */
    EAaPostmortemRetVal_ResourceNotAvailable = 3  /*!< Service is not initialized */
}EAaPostmortemRetVal;


/*@}*/


#ifdef __cplusplus
}
#endif
#endif /* _MCU_RT_IFAAPOSTMORTEM_DEFS_H */
