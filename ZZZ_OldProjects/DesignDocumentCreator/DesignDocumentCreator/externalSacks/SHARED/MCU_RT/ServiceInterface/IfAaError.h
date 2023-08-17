/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Generic error reporting and handling service interface
* @module                AaError
* @owner                 Ksenija Bischof
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAERROR_H
#define _MCU_RT_IFAAERROR_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup dgAaErrorApiLinux AaError LINUX API
 * @ingroup dgAaError
 */

/* @{ */

/**
*******************************************************************************
*   @brief   Set the maximum size of the core file for the calling EE. 
*	     Currently only supported on LRC 
*
*   @param[in] limit  The limiting size, specified in bytes
*
*   @return  EAaErrorRet_Ok
*            EAaErrorRet_Nok  The system call failed.
*
*   @par Description:
*
*            If a signal, whose default behavior trigger the generation of a
*            core dump is received, a core dump is created and truncated to
*            the size specified by the caller.
*            The minimum value between the default one specified by the OS
*            (LFS) and the value specified by the caller will be used.
*            If a value of 0 is passed, no core file will be generated.
*            This is a wrapper for Linux setrlimit().
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Currently only supported on LRC
*
*   @par Example:
*
*   @code
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
******************************************************************************/
EAaErrorRet
AaErrorEeCoreSetMaxSize(u32 limit) __attribute__((const));

/**
*******************************************************************************
*   @brief   Exclude a range of memory pages from a core dump of an EE.
*
*   @param[in]   addr start address (page aligned)
*   @param[in]   len  length in bytes (multiple of a page)
*
*   @return  EAaErrorRet_Ok
*            EAaErrorRet_Nok  The system call failed.
*
*   @par Description:
*
*            If a signal, whose default behavior triggers the generation of a
*            core dump is received, a core dump is created and truncated to
*            the max size specified for this process.
*            With this function it is possible to specify that one or more
*            parts of the EE image should be excluded from the core dump.
*            This is a wrapper for Linux madvise().
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
******************************************************************************/
EAaErrorRet
AaErrorEeCoreExcludePages(void * const addr, u32 len) __attribute__((const));

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*  _MCU_RT_IFAAERROR_H */
