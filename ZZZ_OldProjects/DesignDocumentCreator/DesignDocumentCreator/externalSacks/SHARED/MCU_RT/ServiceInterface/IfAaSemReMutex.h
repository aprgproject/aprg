/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAASEMREMUTEX_H_
#define _MCU_RT_IFAASEMREMUTEX_H_


/**
*@defgroup dgAaSem AaSem API
*/

#include <glo_def.h>
#include <CcsCommon.h>

#include <IfAaSem.h>
#include <IfAaFile_Defs.h>        /* Constant definitions */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSemApiMcu AaSem MCU API
 * @ingroup dgAaSem
 */

/* @{ */

/** @brief Max number of recursive locks on mutex */
#define AASEMREMUTEX_MAX_RECURSIVE_LOCKS 0xFFFF

/**
* @brief Internal struct to keep lock info in memory
* Currently it is important that this structure is aligned corretly but it should
* be taken care of AaSemReMutex implementation anyway. Just warning.
* @note Do not use directly!
*/
typedef struct SAaSemReMutex SAaSemReMutex;

/** @brief Type definition for Re-entrant mutex */
typedef SAaSemReMutex TAaSemReMutex;


/**
*******************************************************************************
*
*   @brief      AaSemReMutexCreate creates and initializes a re-entrant mutex
*
*   @param[out] mutex   Pointer to a placeholder where pointer to new mutex is stored
*
*   @par Description:
*   Function for creating re-entrant mutexes. These mutexes has following features:
*    - Only one EU can hold a mutex at a time.
*    - Only the current owner of the mutex can unlock the mutex.
*    - Recursive locking is allowed.
*    - Equal amount of unlocks compared to locks must be issued by the owner
*      before the mutex becomes unlocked
*
*   @return     None
*
*   @par Errors:
*   Invalid parameters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   Mutex can be shared only inside one EE between EUs. The mutex is always
*   open by default.
*
*   @par Example:
*
*   @code
*
*   See AaSemReMutexDestroy
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
*   @see AaSemReMutexDestroy
*
*******************************************************************************/
void AaSemReMutexCreate( TAaSemReMutex** const mutex );

/**
********************************************************************************
*
*   @brief      AaSemReMutexDestroy destroys the re-entrant mutex.
*
*   @param[in,out]  mutex   Pointer to a placeholder of the mutex.
*
*   @par Description:
*   The mutex placeholder is set to GLO_NULL.
*
*   @return     None
*
*   @par Errors:
*   Invalid parameters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaSemReMutex.h>
*
*   TAaSemRwLock* mutex;
*
*   AaSemReMutexCreate(&mutex);
*
*   AaSemReMutexDestroy(&mutex);
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
*   @see AaSemReMutexCreate
*
******************************************************************************/
void AaSemReMutexDestroy( TAaSemReMutex** const mutex );


/**
********************************************************************************
*
*   @brief      AaSemReMutexLock locks the re-entrant mutex.
*
*   @param[in]  mutex   Pointer to the mutex.
*
*   @par Description:
*   Current lock holder can acquire same lock again without blocking.
*
*   @return     None
*
*   @par Errors:
*   Invalid parameters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   See AaSemReMutexUnlock
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
*   @see AaSemReMutexCreate
*   @see AaSemReMutexUnlock
*
******************************************************************************/
void AaSemReMutexLock( TAaSemReMutex volatile * const mutex );

/**
********************************************************************************
*
*   @brief      AaSemReMutexUnlock unlocks the re-entrant mutex.
*
*   @param[in]  mutex   Pointer to the mutex.
*
*   @par Description:
*   Unlock must be invoked as many times as lock has been acquired by the
*   same lock holder.
*
*   @return     None
*
*   @par Errors:
*   Invalid parameters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaSemReMutex.h>
*
*   TAaSemRwLock* mutex;
*
*   AaSemReMutexCreate(&mutex);
*
*   AaSemReMutexLock(mutex);
*
*   // ... use protected data ...
*
*   AaSemReMutexUnlock(mutex);
*
*   AaSemReMutexDestroy(&mutex);
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
*   @see AaSemReMutexLock
*
******************************************************************************/
void AaSemReMutexUnlock( TAaSemReMutex volatile * const mutex );

/**
********************************************************************************
*
*   @brief      AaSemReMutexGetValue returns current value of internal semaphore.
*
*   @param[in]  mutex       Pointer to mutex.
*   @param[out] semValuePtr Pointer to integer value of mutex (call by reference)
*
*   @par Description:
*   This function returns the current value of internal held semaphore.
*   If the semaphore is not locked, then the referenced value in semValPtr is positive.
*   If the semaphore is locked, then the referenced value in semValPtr is either 0
*   (semaphore is locked, but no other EU is waiting) or negative (absolute value
*   represents the number of EUs waiting).
*   This function internally uses AaSemGetValue().
*
*   @return     None
*
*   @par Errors:
*   Invalid parameters are reported via AaError using code.
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaSemReMutex.h>
*
*   TAaSemRwLock* mutex;
*   i32 mval;
*
*   AaSemReMutexCreate(&mutex);
*
*   // ... use mutex somehow ...
*
*   AaSemReMutexGetValue(mutex, &mval);
*
*   if ( 1 > mval ) {
*       // mutex is locked
*   } else {
*       // mutex is unlocked
*   }
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSemGetValue
*******************************************************************************/
void AaSemReMutexGetValue( TAaSemReMutex* const mutex, i32* semValuePtr);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IFAASEMREMUTEX_H_*/
