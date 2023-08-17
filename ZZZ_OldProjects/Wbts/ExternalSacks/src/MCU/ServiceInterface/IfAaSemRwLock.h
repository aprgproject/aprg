/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_IFAASEMRWLOCK_H_
#define _MCU_IFAASEMRWLOCK_H_

/**
*@defgroup dgAaSem AaSem API
*/

#include <glo_def.h>
#include "CcsCommon.h"
#include <IfAaSem.h>
#include <pthread.h>
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup dgAaSemApiMcu AaSem MCU API
 * @ingroup dgAaSem
 */

/* @{ */



/** @brief Type definition for Re-entrant locks.
*   Internal struct to keep lock info in memory
*   @note Do not use directly! */
typedef struct SAaSemRwLock SAaSemRwLock;

/** @brief Type definition for RW lock */
typedef SAaSemRwLock TAaSemRwLock;


/**
*******************************************************************************
*
*   @brief      Creates and initializes a readers/writer lock
*
*   @param[out] lock   Pointer to a placeholder where pointer to new lock is stored
*
*   @par Description:
*   Summary of readers-writer lock features:
*   - Multiple EUs can hold read lock at a time.
*   - Only one EU can hold write lock at a time and it is always exclusive, thus no
*     read locks can be hold at the same time.
*   - Write lock is favoured over read locks except when there is already write lock
*     being hold in case read and write lock acquirers have fair change to get the lock.
*   - When a write lock is being acquired, no new read locks are accepted (EUs trying
*     to acquire read lock shall be suspended).
*   - When a write lock is being acquired by an EU and there are active read locks,
*     the EU shall be suspended until all read locks are released.
*   - Recursive read locking is allowed, but recursive write locking is NOT allowed.
*
*   @warning Since writers are favoured over readers, starvation is highly probable
*            if there are several writers keeping lock locked for a long time.
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   Lock can be shared only inside one EE between EUs.
*
*   @par Example:
*
*   @code
*
*   TAaSemRwLock * lock;
*
*   AaSemRwLockCreate(&lock);
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
*   @see AaSemRwLockDestroy
*
*******************************************************************************/
void AaSemRwLockCreate( TAaSemRwLock** const lock );

/**
********************************************************************************
*
*   @brief      AaSemRwLockDestroy destroys the readers/writer lock.
*
*   @param[in]  lock   Pointer to the lock placeholder.
*
*   @par Description:
*   The lock placeholder is set to GLO_NULL.
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   TAaSemRwLock * lock;
*
*   AaSemRwLockCreate(&lock);
*
*   AaSemRwLockDestroy(&lock);
*
*   // lock should point to GLO_NULL
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
*   @see AaSemRwLockCreate
*
******************************************************************************/
void AaSemRwLockDestroy( TAaSemRwLock** const lock );

/**
*******************************************************************************
*
*   @brief      AaSemRwLockReadLock acquires read-only lock.
*
*   @param[in]  lock   Pointer to the lock.
*
*   @par Description:
*   If a write lock is already acquired or pending, this call blocks. Multiple
*   read locks from different EUs are allowed at the same time. Recursive read
*   locks from the same EU are not allowed.
*   Requesting read lock from a EU that is holding already the write lock will
*   result in a fatal error i.e termination of curent EU.
*   AaSem will not check for recursive read-only locks but this needs to be ensured by the caller.
*   Recursive read-only locks will lead to a deadlock if they are interleaved
*   with a write lock from another EU.
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*
*   See AaSemRwLockReadUnlock
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
*   @see AaSemRwLockCreate
*   @see AaSemRwLockReadUnlock
*
******************************************************************************/
void AaSemRwLockReadLock( TAaSemRwLock* const lock );

/**
*******************************************************************************
*
*   @brief      AaSemRwLockReadUnlock releases read-only lock.
*               ReadUnlock must be called same number of times as ReadLock - but from different EUs()
*               as recursive read locks from the same EU are not allowed.
*
*   @param[in]  lock   Pointer to the lock.
*
*   @par Description:
*   None
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*
*   @par Example:
*   @code
*
*   SAaSemRwLock* lock;
*
*   AaSemRwLockCreate(&lock);
*
*   AaSemRwLockReadLock(lock);
*
*   // ... read access to data acquired ...
*
*   AaSemRwLockReadUnlock(lock);
*
*   AaSemRwLockDestroy(&lock);
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
*   @see AaSemRwLockCreate
*   @see AaSemRwLockReadLock
*
******************************************************************************/
void AaSemRwLockReadUnlock( TAaSemRwLock* const lock );

/**
*******************************************************************************
*
*   @brief      AaSemRwLockWriteLock acquires exclusive write lock.
*
*   @param[in]  lock   Pointer to the lock.
*
*   @par Description:
*   If active read locks or write lock exists, this call blocks. Write lock
*   is favoured over read locks. Recursive write locks are not allowed for same EU
*   and will result in a fatal error i.e stopping of current EU
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*
*   // See AaSemRwLockWriteUnlock
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
*   @see AaSemRwLockCreate
*   @see AaSemRwLockWriteUnlock
*
******************************************************************************/
void AaSemRwLockWriteLock( TAaSemRwLock* const lock );

/**
*******************************************************************************
*
*   @brief      AaSemRwLockWriteUnlock releases write lock.
*
*   @param[in]  lock   Pointer to the lock.
*
*   @par Description:
*   None
*
*   @return     None
*
*   @par Errors:
*   Invalid paramters are reported via AaError using code
*   EAaErrorCcs_AaSem_InvalidParameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*
*   TAaSemRwLock* lock;
*
*   AaSemRwLockCreate(&lock);
*
*   AaSemRwLockWriteLock(lock);
*
*   // ... write access to data acquired ...
*
*   AaSemRwLockWriteUnlock(lock);
*
*   AaSemRwLockDestroy(&lock);
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
*   @see AaSemRwLockCreate
*   @see AaSemRwLockWriteLock
*
******************************************************************************/
void AaSemRwLockWriteUnlock( TAaSemRwLock* const lock );

/* @} */


#ifdef __cplusplus
}
#endif



#endif /* _MCU_IFAASEMRWLOCK_H_*/
