/**
*******************************************************************************
* @file
* $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaTestPort MCU Definitions.
*
* Copyright 2015 Nokia Soultions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AATESTPORT_DEF_H_
#define _MCU_IF_AATESTPORT_DEF_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/Definitions/IfAaTestPort_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaTestPortMcuDefs AaTestPort Definitions (MCU)
 * @ingroup dgAaTestPort
 */

/*@{*/

/*!
 * Maximum length of AaTestPort client name (with terminator)
 */
#define AATESTPORT_CLIENT_MAX_NAME_LENGTH 32

/*!
 * Minimum value of MSS socket option
 */
#define AATESTPORT_TCP_MIN_MSS 88

/*!
 * A type for AaTestPort Client socket options
 */
typedef struct AaTestPortClientSocketOptions
{
    u32 maxSegmentSize;       /*!< socket option for setting max segment size, 0 means not set*/
}AaTestPortClientSocketOptions;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AATESTPORT_DEF_H_
