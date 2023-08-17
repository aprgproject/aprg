/** @file
*   @brief AaCpu service API header file
*   @copyright 2014 Nokia Solutions and Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _IFAACPU_H
#define _IFAACPU_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@defgroup dgAaCpu Core Control Service (AaCpu)
*@ingroup dgDriverSw
*
* Common Computer and Support SW Core Control Service.
*
* This service is divided into following subsystems:
*  - Atomic operations
*  - Spinlocks
*  - CPU relinquishment
*  - CPU high resolution timestamp
*  - Bit manipulation
*
* API naming rules AaCpu<subsystem><operation> e.g. AaCpuSpinLockTryLock
* where 
*  - SpinLock is subsystem
*  - TryLock is operation
*
*
* @par Atomic operations
* TBD
*
* @par Spinlocks
* Spinlocks are so-called <i>busy-wait-loops</i> where lock acquirer waits in 
* a loop by pollig the lock state to be free. Spinlocks are usable only in 
* special cases like short term lock when systems calls causes too much overhead. 
* CC&S spinlock implementation is intended for userspace applications in 
* uniprocessor and SMP systems. 
* \n\n
* There are some issues between SMP and uniprocessor machines what comes to spinning.
* In SMP, it might be more feasible to sleep for a while than do raw spinning with yield 
* if the lock is not released after a few tryouts since sleeping gives other EUs opportunity
* scheduled in to the CPU running the waiting EU and also utilization of shared memory bus
* does not get too high due to spinning. On the other hand in uniprocessor systems this issues
* is not so important except if there is some CPU peripherals such as DMA controller using
* also the same memory bus. E.g. in PPC440 CPUs there are integrated DMA controller and
* the priority of the access to the bus can be configured thus the excessinv spinning 
* may not be a problem in every systems.
* \n\n
* There may also be CPU specific issues what comes to effectiveness of spinlock. E.g in 
* PowerPC systems, the implementation of spinlock contains only a read operation in case
* of the lock already reserved. However in x86 environments, implementation is based on
* atomic exchange operation involving write access to the memory even if already locked.
* In that sense PowerPC implementation is much more economical than x86 what comes to
* memory bus utilization. If implementation for x86 would be made more economical then
* the actual implementation of the spinlock would become more complex. 
* \n\n
* The implementation should be able to adapt itself automatically at runtime to minimize 
* system call overhead and to maintain niceness of the user even in case of lock being heavily 
* contended and variable length lockings took place. There is however no guarantee for
* fairness of locking although the adaptation tries to give some level of fairness.
* \n\n
* Also in some systems (especially if using round robin scheduling) priority inversion
* is a problem. This is however under studying and may eventually lead to a new API call.
* \n\n
* In the contrast to semaphores, spinlocks can be initialized statically.
* \n
* @warning Spinlock is a dangerous synchronization mechanism and can lead to
*          starvation in some OSes. A good rule of thumb is that all EUs should
*          have same priority sharing same spinlock. Also atleast AaCpuYield
*          should be called if a locking fails before retrying. Also the lock
*          should only be locked for a very short of time compared to OS scheduling
*          time.
* 
* @par CPU relinquishment
* TBD
*
* @par CPU performance counter
* TBD
*
* @par Bit field manipulation
* Endianess conversion. TBD
*
* 
* @see http://www.cis.temple.edu/~ingargio/cis307/readings/spinsem.html
*
*/

/**
*@defgroup dgAaCpuApi API
*@ingroup dgAaCpu
*
* Application Programming Interface.
* 
* API specification (current): https://pi.inside.nokiasiemensnetworks.com/urn.htm?id=09006c378127eb91&DMW_DOCBASE=espoo11&auth=T&version=current&document_id=13-575726
*
* CC&S Wiki for AaMem: http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaCpu
* 
*@{*/

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>
#include <stddef.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* There are differences between compilers inlining */
/** @cond */
#ifndef __CCS_INLINE__
#define __CCS_INLINE__ __inline__
#endif
/** @endcond */

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/** @brief Type definition for spinlock 
*
*  Users should not access to members directly.
*/
typedef struct SAaCpuSpinLock
{
    volatile i32 value;        /**< Spinlock value #AACPU_SPINLOCK_LOCKED or #AACPU_SPINLOCK_UNLOCKED */
    volatile i32 spinThold;    /**< Spin threshold for adaptive spinning (changed dynamically by AaCpuSpinLockLock()) */
    volatile i32 yieldThold;   /**< Yield threshold for adaptive spinning (changed dynamically by AaCpuSpinLockLock()) */
} TAaCpuSpinLock;

#define AACPU_SPINLOCK_LOCKED   0 /** @brief Value of locked spinlock */
#define AACPU_SPINLOCK_UNLOCKED 1 /** @brief Value of unlocked spinlock */
#define AACPU_SPINLOCK_INIT     AACPU_SPINLOCK_UNLOCKED /** @brief By default the lock is free */

#define AACPU_SPINLOCK_MAX_SPINS 50
#define AACPU_SPINLOCK_MAX_YIELDS 1000

/** @brief Type definition for 32bit atomic address 
*
*  Users should not access to members directly.
*/
typedef struct SAaCpuAtomic32
{
    volatile i32 data; /**< Value of the 32 bit atomic data */
} TAaCpuAtomic32;

/** @brief Type definition for 64bit atomic address 
*
*  Users should not access to members directly.
*/
typedef struct SAaCpuAtomic64
{
    TAaCpuSpinLock lock; /**< Lock may or may not be used by the actual implementation */
    volatile i64 data;   /**< Value of the 64 bit atomic data */
} TAaCpuAtomic64;



/*----------------------- PUBLIC INTERFACES (API 32bit) ----------------------------------*/

/**
 * @defgroup dgAaCpuApiCommon AaCpu COMMON API
 * @ingroup  dgAaCpu
 */

/* @{ */


/*----------------------- PUBLIC INTERFACES (API 32bit) ----------------------------------*/


/**
*******************************************************************************
*
*   @brief    Sets 32bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  32bit value to be written.
*
*   @return None
*
*   @par Description:
*   32bit atomic write to given 32bit atomic variable.
* 
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*
*   AaCpuAtomicSet32(&var, 0xE550);
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
void AaCpuAtomicSet32 (TAaCpuAtomic32 * atomic, const i32 value);

/**
*******************************************************************************
*
*   @brief    Reads 32bit value atomically
*
*
*   @param[in] atomic   Pointer to atomic variable.
*
*   @return 32bit data
*
*   @par Description:
*   Reads atomically 32bit value of given atomic variable.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*
*   AaCpuAtomicSet32(&var, 0xE550);
*
*   if (AaCpuAtomicRead32(&var) == 0xE550)
*   {
*     // Read data should match written one
*   }
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
i32 AaCpuAtomicRead32 (TAaCpuAtomic32 * atomic);

/**
*******************************************************************************
*
*   @brief    Adds 32bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  32bit value to be added.
*
*   @return Value of the atomic variable after addition
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   See AaCpuAtomicSub32
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
*   @see AaCpuAtomicSub32
*
******************************************************************************/
i32 AaCpuAtomicAdd32 (TAaCpuAtomic32 * atomic, const i32 value);


/**
*******************************************************************************
*
*   @brief    Substracts 32bit data atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  32bit value to be substracted.
*
*   @return Value of the atomic variable after substraction
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var = AACPU_ATOMIC_STATIC_INIT32(1);
*
*   AaCpuAtomicAdd32(&var, 2);
*
*   AaCpuAtomicSub32(&var, 4);
*
*   if (AaCpuAtomicRead32(&var) == -1)
*   {
*     // Read data should be 1 + 2 - 4 = -1
*   }
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
*   @see AaCpuAtomicAdd32
*
******************************************************************************/
i32 AaCpuAtomicSub32 (TAaCpuAtomic32 * atomic, const i32 value);

/**
*******************************************************************************
*
*   @brief    Increments 32bit value by 1 atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Value of the atomic variable after incrementation
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   See AaCpuAtomicDec32
*
*   @endcode
*
*   @par Usage:
*   This kind of atomic operation is usefull e.g. in reference counting.
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
i32 AaCpuAtomicInc32 (TAaCpuAtomic32 * atomic);


/**
*******************************************************************************
*
*   @brief    Decrement 32bit value by 1 atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Value of the atomic variable after decrementation
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*
*   AaCpuAtomicSet32(&var, 0);
*
*   AaCpuAtomicDec32(&var);
*   AaCpuAtomicDec32(&var);
*
*   AaCpuAtomicInc32(&var);
*   AaCpuAtomicInc32(&var);
*   AaCpuAtomicInc32(&var);
*
*   if (AaCpuAtomicRead32(&var) == 1)
*   {
*     // Read data should be 0 - 1 - 1 + 1 + 1 + 1 = 1
*   }
*
*   @endcode
*
*   @par Usage:
*   This kind of atomic operation is usefull e.g. in reference counting.
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
i32 AaCpuAtomicDec32 (TAaCpuAtomic32 * atomic);


/**
*******************************************************************************
*
*   @brief    Swaps 32bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  32 bit value to swap.
*
*   @return Value of the atomic variable before swapping
*
*   @par Description:
*   This function swaps atomically given 32bit value with atomic variable and 
*   returns the value in the atomic variable <i>before</i> swapping.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 10);
*
*   temp = AaCpuAtomicSwap32(&var, -10);
*
*   if (temp == 10)
*   {
*       // temp should be the value in the atomic variable before swapping
*   }
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
i32 AaCpuAtomicSwap32 (TAaCpuAtomic32 * atomic, i32 value);


/**
*******************************************************************************
*
*   @brief    Compares 32bit data and if equal swap atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   32 bit value to compare.
*   @param[in]     value  32 bit value to swap.
*
*   @return If <i>equal</i> #comp or if <i>not equal</i> the atomic variable before swapping
*
*   @par Description:
*   This function compares given atomic variable to given comparison value
*   and if the current value of the atomic variable <i>equals</i> with given comparison
*   value, the atomic variable value is swapped to given swap value and comparison
*   value is returned. If the current atomic variable value and comparison value 
*   do not match, swapping is not done and the current value of the atomic variable 
*   is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 10);
*
*   temp = AaCpuAtomicCmpSwap32(&var, 10, -10);
*
*   if (temp == 10)
*   {
*       // If temp equals to comparison value (10), swap succeeded
*   }
*   else
*   {
*       // Temp did not match so it contains current value of the
*       // atomic variable
*   }
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
i32 AaCpuAtomicCmpSwap32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value);


/**
*******************************************************************************
*
*   @brief Adds 32bit data atomically if given value
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   32 bit value to compare.
*   @param[in]     value  32 bit value to add.
*
*   @return Previous value or #comp if equal.
*
*   @par Description:
*   This function compares given atomic variable to given comparison value
*   and if the current value of the atomic variable <i>does equal</i> with 
*   given comparison value, the atomic variable value is added with given value 
*   and atomic variable value after adding is returned. If the current atomic 
*   variable value and comparison value <i>does not equal</i>, adding is not done and 
*   the comparison value is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 9);
*
*   temp = AaCpuAtomicAddUnless32(&var, 10, -10);
*
*   if (temp != 10)
*   {
*       // If temp not equal to comparison value (10), adding succeeded
*       // and temp contains the atomic variable value before adding
*   }
*   else
*   {
*       // Temp equals to comparison value so adding not done
*   }
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

i32 AaCpuAtomicAddIf32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value);


/**
*******************************************************************************
*
*   @brief Adds 32bit data atomically unless given value
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   32 bit value to compare.
*   @param[in]     value  32 bit value to add.
*
*   @return Previous value or #comp if equal.
*
*   @par Description:
*   This function compares given atomic variable to given comparison value
*   and if the current value of the atomic variable does <i>not equal</i> with 
*   given comparison value, the atomic variable value is added with given value 
*   and atomic variable value before adding is returned. If the current atomic 
*   variable value and comparison value <i>equals</i>, adding is not done and 
*   the comparison value is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 9);
*
*   temp = AaCpuAtomicAddUnless32(&var, 10, -10);
*
*   if (temp != 10)
*   {
*       // If temp not equal to comparison value (10), adding succeeded
*       // and temp contains the atomic variable value before adding
*   }
*   else
*   {
*       // Temp equals to comparison value so adding not done
*   }
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
i32 AaCpuAtomicAddUnless32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value);

/**
*******************************************************************************
*
*   @brief Increments 32bit data by 1 atomically if not zero
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Previous value or 0 if already zero.
*
*   @par Description:
*   This function increments given atomic variable by 1 <i>if and only if</i> 
*   the atomic variable value <i>is not</i> zero (0) and returns the value 
*   before increment. If the value is zero, the atomic variable is not 
*   incremented and 0 is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, -1);
*
*   temp = AaCpuAtomicIncNotZero32(&var);
*
*   if (temp != 0)
*   {
*       // If temp not equal to zero (0), increment succeeded since
*       // atomic variable was not zero during increment
*   }
*   else
*   {
*       // Temp is zero so atomic variable was zero too.
*   }
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
i32 AaCpuAtomicIncNotZero32 (TAaCpuAtomic32 * atomic);

/**
*******************************************************************************
*
*   @brief Decrements 32bit data by 1 atomically if not zero
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Previous value or 0 if already zero.
*
*   @par Description:
*   This function decrements given atomic variable by 1 <i>if and only if</i> 
*   the atomic variable value <i>is not</i> zero (0) and returns the value 
*   before increment. If the value is zero, the atomic variable is not 
*   decremented and 0 is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, -1);
*
*   temp = AaCpuAtomicDecNotZero32(&var);
*
*   if (temp != 0)
*   {
*       // If temp not equal to zero (0), decrement succeeded since
*       // atomic variable was not zero during increment
*   }
*   else
*   {
*       // Temp is zero so atomic variable was zero too and decrement
*       // is not done.
*   }
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
i32 AaCpuAtomicDecNotZero32 (TAaCpuAtomic32 * atomic);


/**
*******************************************************************************
*
*   @brief Adds 32bit data atomically if greater than given value
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   32 bit value to compare.
*   @param[in]     value  32 bit value to add.
*
*   @return Previous value or #comp if <i>not</i> greater
*
*   @par Description:
*   This function adds given value to given atomic variable <i>if and only if</i> 
*   the atomic variable value is <i>greater than</i> given comparison value and 
*   returns the value before adding. If the atomic variable value is <i>equal or
*   smaller</i> than the comparison value, the atomic variable is not added and
*   comparison value is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 20);
*
*   temp = AaCpuAtomicAddGreater32(&var, 19, 5);
*
*   if (temp != 19)
*   {
*       // If temp not equal to comparison value, adding succeeded
*       // and temp shall be the value before adding (20)
*   }
*   else
*   {
*       // Temp is comparison value so adding not done.
*   }
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
i32 AaCpuAtomicAddGreater32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value);

/**
*******************************************************************************
*
*   @brief Decrements 32bit data atomically if greater than given value
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   32 bit value to compare.
*   @param[in]     value  32 bit value to decrement.
*
*   @return Previous value or #comp if <i>not</i> greater
*
*   @par Description:
*   This function decrements given value to given atomic variable <i>if and only if</i> 
*   the atomic variable value is <i>greater than</i> given comparison value and 
*   returns the value before decrement. If the atomic variable value is <i>equal 
*   or smaller</i> than the comparison value, the atomic variable is not
*   decremented and comparison value is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic32 var;
*   i32            temp;
*
*   AaCpuAtomicSet32(&var, 20);
*
*   temp = AaCpuAtomicDecGreater32(&var, 19, 5);
*
*   if (temp != 19)
*   {
*       // If temp not equal to comparison value, decrement succeeded
*       // and temp shall be the value before decrement (20)
*   }
*   else
*   {
*       // Temp is comparison value so decrement not done.
*   }
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
i32 AaCpuAtomicDecGreater32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value);


/** @cond */
/** @brief For compatibility with old SW */
#define AaCpuAtomicDecIfPos32(__atomic) AaCpuAtomicDecGreater32((__atomic), 0, 1);
/** @endcond */





/*----------------------- PUBLIC INTERFACES ( API 64bit) ----------------------------------*/




/*----------------------- PUBLIC INTERFACES (API 64bit) ----------------------------------*/


/**
*******************************************************************************
*
*   @brief    Sets 64bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  64bit value to be written.
*
*   @return None
*
*   @par Description:
*   64bit atomic write to given 64bit atomic variable.
* 
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic64 var;
*
*   AaCpuAtomicSet64(&var, 0x11100010E550ABBALLU); /// @note LLU suffix not supported by some compilers
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
*   @see AaCpuAtomicRead64
*
******************************************************************************/
void AaCpuAtomicSet64 (TAaCpuAtomic64 * atomic, const i64 value);

/**
*******************************************************************************
*
*   @brief    Reads 64bit value atomically
*
*
*   @param[in] atomic   Pointer to atomic variable.
*
*   @return 64bit data
*
*   @par Description:
*   32bit atomic read from given 64bit atomic variable.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic64 var;
*
*   AaCpuAtomicSet64(&var, 0x11100010E550ABBALLU); /// @note LLU suffix not supported by some compilers
*
*   if (AaCpuAtomicRead64(&var) == 0x11100010E550ABBALLU)
*   {
*     // Read data should match written one
*   }
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
*   @see AaCpuAtomicSet64
*
******************************************************************************/
i64 AaCpuAtomicRead64 (TAaCpuAtomic64 * atomic);

/**
*******************************************************************************
*
*   @brief    Adds 64bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  64bit value to be added.
*
*   @return Value of the atomic variable after addition
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   See AaCpuAtomicSub64
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
*   @see AaCpuAtomicSub64
*
******************************************************************************/
i64 AaCpuAtomicAdd64 (TAaCpuAtomic64 * atomic, const i64 value);

/**
*******************************************************************************
*
*   @brief    Substracts 64bit value atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     value  64bit value to be substracted.
*
*   @return Value of the atomic variable after substraction
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic64 var = AACPU_ATOMIC_STATIC_INIT64(1);
*
*   AaCpuAtomicAdd64(&var, 2);
*
*   AaCpuAtomicSub64(&var, 4);
*
*   if (AaCpuAtomicRead64(&var) == -1)
*   {
*     // Read data should be 1 + 2 - 4 = -1
*   }
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
*   @see AaCpuAtomicAdd64
*
******************************************************************************/
i64 AaCpuAtomicSub64 (TAaCpuAtomic64 * atomic, const i64 value);


/**
*******************************************************************************
*
*   @brief    Increments 64bit value by 1 atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Value of the atomic variable after incrementation
*
*   @par Description:
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   See AaCpuAtomicDec64
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
*   @see AaCpuAtomicDec64
*
******************************************************************************/
i64 AaCpuAtomicInc64 (TAaCpuAtomic64 * atomic);

/**
*******************************************************************************
*
*   @brief    Decrement 64bit value by 1 atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*
*   @return Value of the atomic variable after decrementation
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic64 var;
*
*   AaCpuAtomicSet64(&var, 0);
*
*   AaCpuAtomicDec64(&var);
*   AaCpuAtomicDec64(&var);
*
*   AaCpuAtomicInc64(&var);
*   AaCpuAtomicInc64(&var);
*   AaCpuAtomicInc64(&var);
*
*   if (AaCpuAtomicRead64(&var) == 1)
*   {
*     // Read data should be 0 - 1 - 1 + 1 + 1 + 1 = 1
*   }
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
*   @see AaCpuAtomicInc64
*
******************************************************************************/
i64 AaCpuAtomicDec64 (TAaCpuAtomic64 * atomic);

/**
*******************************************************************************
*
*   @brief    Compares 64bit data and if equal swap atomically
*
*
*   @param[in,out] atomic Pointer to atomic variable.
*   @param[in]     comp   64 bit value to compare.
*   @param[in]     value  64 bit value to swap.
*
*   @return If <i>equal</i> #comp or if <i>not equal</i> the atomic variable before swapping
*
*   @par Description:
*   This function compares given atomic variable to given comparison value
*   and if the current value of the atomic variable <i>equals</i> with given comparison
*   value, the atomic variable value is swapped to given swap value and comparison
*   value is returned. If the current atomic variable value and comparison value 
*   do not match, swapping is not done and the current value of the atomic variable 
*   is returned.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Address must be 32bit aligned. Otherwice operation may not be atomic.
*   There is no runtime checking related to the aligment.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuAtomic64 var;
*   i32            temp;
*
*   AaCpuAtomicSet64(&var, 10);
*
*   temp = AaCpuAtomicCmpSwap64(&var, 10, -10);
*
*   if (temp == 10)
*   {
*       // If temp equals to comparison value (10), swap succeeded
*   }
*   else
*   {
*       // Temp did not match so it contains current value of the
*       // atomic variable
*   }
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
i64 AaCpuAtomicCmpSwap64 (TAaCpuAtomic64 * atomic, i64 comp, i64 value);





/*----------------------- PUBLIC INTERFACES (Spinlock API) ----------------------------------*/



/** @cond
* @brief For compatibility reasons (not in Doxygen document) */
#define AaGpuSpinLockInit AaCpuSpinLockInit
/** @endcond */


/*----------------------- PUBLIC INTERFACES (Spinlock API) ----------------------------------*/



/**
*******************************************************************************
*
*   @brief   Initializes a spinlock
*
*
*   @param[in] lock  Pointer to spinlock.
*
*   @return None
*
*   @par Description:
*   Initilizes a spinlock.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*       Address must be 32bit aligned.
*
*   @par Example:
*
*   @code
*
*   TAaCpuSpinLock spinlock;
*
*   // Init must be done otherwice AaCpuSpinLockTryLock will fail
*   // always and AaCpuSpinLockLock gets stuck.
*   AaCpuSpinLockInit(&spinlock); 
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
*   @see AaCpuSpinLockTryLock
*   @see AaCpuSpinLockUnlock
*   @see AACPU_SPINLOCK_STATIC_INIT
*
******************************************************************************/
void AaCpuSpinLockInit (TAaCpuSpinLock * lock);

/**
*******************************************************************************
*
*   @brief    Tries to lock a spinlock
*
*
*   @param[in] lock  Pointer to a spinlock.
*
*   @return 1 if locking succeeded, otherwice 0
*
*   @par Description:
*   Tries to lock given spinlock atomically. If locking succeeds (the lock is
*   not locked by somebody else), 1 is returned. Otherwice 0 is returned. 
*   In case of lock failure, it might be feasible to call AaCpuYield() before
*   re-trying since AaCpuYield() may give the current lock holder opportunity
*   to release the lock. See AaCpuYield() for more details.
* 
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Lock address must be 32bit aligned. Does not support re-entrancy i.e.
*   re-acquiring the lock in the same EU leads to deadlock.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuSpinLock spinlock;
*
*   // Init must be done otherwice AaCpuSpinLockTryLock will fail
*   // always and AaCpuSpinLockLock gets stuck.
*   AaCpuSpinLockInit(&spinlock); 
* 
*   // Try to acquire the lock and spin if fails
*   while (!AaCpuSpinLockTryLock(&spinlock))
*   {
*       // Yield the CPU so that the current lock holder has a better
*       // change to release the lock before we retry to acquire it.
*       AaCpuYield();
*       // Also AaSysTime can be used here to create some delay however
*       // we may end up to starvation if somebody is trying to get the
*       // lock and not using AaSysTime.
*   }
* 
*   // Lock acquired, do something with data it protects....
* 
*   // Lock can now be released
*   AaCpuSpinLockUnlock(&spinlock);
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
*   @see AaCpuSpinLockInit
*   @see AaCpuSpinLockUnlock
*   @see AaCpuSpinLockLock
*   @see AaCpuYield 
*
******************************************************************************/
i32 AaCpuSpinLockTryLock (TAaCpuSpinLock * lock);

/**
*******************************************************************************
*
*   @brief    Locks a spinlock
*
*
*   @param[in] lock  Pointer to a spinlock.
*
*   @return None
*
*   @par Description:
*   Locks given spinlock atomically. If the lock already acquired, spins internally
*   until the lock becomes free. Spinning is adaptive thus heavily contended lock
*   may cause acquiring EU to sleep. However spinlocks should not be used in case
*   of need for long term locking or if extensive contention is possible.
* 
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Lock address must be 32bit aligned. Does not support re-entrancy i.e.
*   re-acquiring the lock in the same EU leads to deadlock.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuSpinLock spinlock;
*
*   // Init must be done otherwice AaCpuSpinLockLock will cause deadlock.
*   AaCpuSpinLockInit(&spinlock); 
* 
*   // Acquire the lock 
*   AaCpuSpinLockLock(&spinlock))
* 
*   // Lock acquired, do something with data it protects....
* 
*   // Lock can now be released
*   AaCpuSpinLockUnlock(&spinlock);
*
*   @endcode
*
*   @par Usage:
*   Compared to AaCpuSpinLockTryLock() with AaCpuYield(), this function
*   is much more "nice" to other EUs since in case of contented lock
*   this function tries to adapt the ratio between spinning and sleeping.
*   In case of non-contented lock, performance is almost identical to
*   AaCpuSpinLockTryLock() with AaCpuYield().  
*
*   @par Rationale:
*   Substitute implementation for AaCpuSpinLockTryLock() is needed in
*   case of contended lock since AaCpuSpinLockTryLock() with AaCpuYield()
*   causes a lot of useless CPU (and memory bus) load and may cause
*   starvation in lower priority EUs.
*
*   @par Future directions:
*   None
*
*   @see AaCpuSpinLockInit
*   @see AaCpuSpinLockUnlock
*   @see AaCpuSpinLockTryLock 
*
******************************************************************************/
void AaCpuSpinLockLock (TAaCpuSpinLock * lock);

/**
*******************************************************************************
*
*   @brief    Unlocks a spinlock
*
*
*   @param[in] lock  Pointer to spinlock.
*
*   @return None
*
*   @par Description:
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Lock address must be 32bit aligned.
*
*   @par Example:
*
*   @code
*
*   See AaCpuSpinLockTryLock
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
*   @see AaCpuSpinLockInit
*   @see AaCpuSpinLockTryLock  
*
******************************************************************************/
void AaCpuSpinLockUnlock (TAaCpuSpinLock * lock);

/**
*******************************************************************************
*
*   @brief    Returns current spinlock value
*
*
*   @param[in] lock  Pointer to spinlock.
*
*   @return #AACPU_SPINLOCK_UNLOCKED if the lock is free
*   @return #AACPU_SPINLOCK_LOCKED if the lock is NOT free
*
*   @par Description:
*   Since spinlock work as a binary semaphore, only two return values are
*   possible. If the spinlock is not owned or protected by the caller of this 
*   function, return value may changed during invocations.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   Lock address must be 32bit aligned.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   TAaCpuSpinLock spinlock;
*
*   // Init must be done otherwice AaCpuSpinLockTryLock will fail
*   // always.
*   AaCpuSpinLockInit(&spinlock); 
* 
*   // Check spinlock state
*   if (AaCpuSpinLockGet(&spinlock) == AACPU_SPINLOCK_UNLOCKED)
*   {
*       // Spinlock must be in unlocked state since not yet acquired
*   }
*
*   // Try to acquire the lock and spin if fails
*   while (!AaCpuSpinLockTryLock(&spinlock))
*   {
*       // Yield the CPU so that the current lock holder has a better
*       // change to release the lock before we retry to acquire it.
*       AaCpuYield();
*       // Also AaSysTime can be used here to create some delay however
*       // we may end up to starvation if somebody is trying to get the
*       // lock and not using AaSysTime.
*   }
* 
*   // Lock acquired, do something with data it protects....
* 
*   // Check spinlock state
*   if (AaCpuSpinLockGet(&spinlock) == AACPU_SPINLOCK_LOCKED)
*   {
*       // Spinlock must be in locked state since we own it
*   }
*
*   // Lock can now be released
*   AaCpuSpinLockUnlock(&spinlock);
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
*   @see AaCpuSpinLockInit
*   @see AaCpuSpinLockTryLock
*
******************************************************************************/
i32 AaCpuSpinLockGet (TAaCpuSpinLock * lock);

/** @} */

/** @name CPU relinquishment API
* @{
*/

/**
*******************************************************************************
*
*   @brief    Yields the CPU
*
*
*   @param None
*
*   @return None
*
*   @par Description:
*   Yields OS to force the current EU to relinquish the processor until the EU
*   becomes again active EU. It is however up to OS wether new lower priority
*   EU is scheduled in or not, if ready to run, or the calling EU is re-scheduled. 
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
*   See AaCpuSpinLockUnlock
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
void AaCpuYield (void);

/** @} */



/** @name CPU performance counter API
* @{
*/

/** @brief Maximum value of timebase */
#define AACPU_MAX_TIMEBASE CCS_STATIC_CAST(u64,-1)

/**
*******************************************************************************
*
*   @brief    Calculates difference between two timebase values
*   @def AACPU_TIMEBASE_DIFF_GET
*
*   @param[in] __begin  Start time
*   @param[in] __end    End time
*
*   @return Difference between two timebase values
*
*   @par Description:
*   None
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
*   See AaCpuTimeBaseGet()
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
*   @see AaCpuTimeBaseGet
*
******************************************************************************/
#define AACPU_TIMEBASE_DIFF_GET(__begin, __end) \
    ((__begin) < (__end)) ? ((__end) - (__begin)) : \
                            ((__end) + (AACPU_MAX_TIMEBASE - (__begin)))

/**
*******************************************************************************
*
*   @brief    Returns current 64bit timestamp value
*
*
*   @param None
*
*   @return Current 64bit timestamp value
*
*   @par Description:
*   Timebase value is queried directly from CPU. It is unspecified in which unit
*   timebase value is defined.
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
*   #include <IfAaCpu.h>
*
*   u64 begin, end, difference;
*
*   begin = AaCpuTimeBaseGet();
*
*   // Do some things
*
*   end = AaCpuTimeBaseGet();
*
*   // Calculate how long it took to do some things in timebase units
*   difference = AACPU_TIMEBASE_DIFF_GET(begin, end);
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
*   @see AACPU_TIMEBASE_DIFF_GET
*
******************************************************************************/
u64 AaCpuTimeBaseGet (void);

/** @cond */
/** @brief For supporting old-styled API call naming */
#define AaCpuReadTimeBase AaCpuTimeBaseGet
/** @endcond */

/** @} */


/** @name Bit field manipulation API
* @{
*/

/**
*******************************************************************************
*
*   @brief  Returns the natural byte order of the CPU
*
*
*   @param None
*
*   @return In big endian system >0, in little endian system <0 or 0 if cannot 
*           be detected.
*
*   @par Description:
*   This function returns byte ordering of a CPU (little or big endian).
*   Current system endianness can also be detected at build time using 
*   __CCS_BIG_ENDIAN__ and __CCS_LITTLE_ENDIAN__ preprocessor defines.
*
*   @par Errors:
*   None
* 
*   @par Restrictions:
*   If system supports bi-endianness, this function returns only the endianness 
*   visible to application domain the code is executing. E.g. some memory 
*   location is marked as little endian mode at the same time the SW is executed 
*   in big endian mode.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   int endianess = AaCpuBitGetByteOrder();
*
*   if (endianess > 0)
*   {
*       // Big endian CPU
*   }
*   else if (endianess < 0)
*   {
*       // Little endian CPU
*   }
*   else
*   {
*       // Oops?
*   }
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
*   @see None
*
******************************************************************************/
i32 AaCpuBitGetByteOrder (void);

/**
*******************************************************************************
*
*   @brief  Changes 16bit value in given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to 16bit unsigned value to convert
*
*   @return Original value before byte order change
*
*   @par Description:
*   This function changes byte order of 16bit value in given address. 
*   Original value is also returned.
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
*   #include <IfAaCpu.h>
*
*   u16 result, value = 0xCAFE;
*
*   result = AaCpuBitSwapByteOrder16(&value);
*
*   if ((result != value) && 
*       (result == 0xCAFE) &&
*       (value == 0xFECA))
*   {
*       // Result value should match to original value
*   }
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
*   @see AaCpuBitSwapMultiByteOrder16
*
******************************************************************************/
u16 AaCpuBitSwapByteOrder16 (u16 * valuePtr);

/**
*******************************************************************************
*
*   @brief  Changes multiple 16bit values starting from given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to start of 16bit unsigned values to convert
*   @param[in] length    Number of 16bit values to convert
*
*   @return None
*
*   @par Description:
*   This function changes byte order of 16bit values starting from given address
*   until given number of values has been converted. If #count is set to 0 and/or 
*   #valuePtr is set to GLO_NULL, no byte order conversion takes place.
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
*   #include <IfAaCpu.h>
*
*   u16 values[] = {0x1, 0x2, 0x3, 0xCAFE};
*
*   AaCpuBitSwapMultiByteOrder16(values, sizeof(values) / sizeof(u16));
*
*   // values array should now have following content:
*   // values[0] == 0x0100;
*   // values[1] == 0x0200;
*   // values[2] == 0x0300;
*   // values[3] == 0xFECA;
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
*   @see AaCpuBitSwapByteOrder16
*
******************************************************************************/
void AaCpuBitSwapMultiByteOrder16 (u16 * valuePtr, size_t length);


/**
*******************************************************************************
*
*   @brief  Changes 32bit value in given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to 32bit unsigned value to convert
*
*   @return Original value before byte order change
*
*   @par Description:
*   This function changes byte order of 32bit value in given address. 
*   Original value is also returned.
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
*   #include <IfAaCpu.h>
*
*   u32 result, value = 0xE550CAFE;
*
*   result = AaCpuBitSwapByteOrder32(&value);
*
*   if ((result != value) && 
*       (result == 0xE550CAFE) && 
*       (value == 0xFECA50E5))
*   {
*       // Result value should match to original value
*   }
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
*   @see AaCpuBitSwapMultiByteOrder32
*
******************************************************************************/
u32 AaCpuBitSwapByteOrder32 (u32 * valuePtr);

/**
*******************************************************************************
*
*   @brief  Changes multiple 32bit values starting from given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to start of 32bit unsigned values to convert
*   @param[in] length    Number of 32bit values to convert
*
*   @return None
*
*   @par Description:
*   This function changes byte order of 32bit values starting from given address
*   until given number of values has been converted. If #count is set to 0 and/or 
*   #valuePtr is set to GLO_NULL, no byte order conversion takes place.
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
*   #include <IfAaCpu.h>
*
*   u32 values[] = {0x1, 0x2, 0x3, 0xABBACAFE};
*
*   AaCpuBitSwapMultiByteOrder16(values, sizeof(values) / sizeof(u32));
*
*   // values array should now have following content:
*   // values[0] == 0x01000000;
*   // values[1] == 0x02000000;
*   // values[2] == 0x03000000;
*   // values[3] == 0xFECABAAB;
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
*   @see AaCpuBitSwapByteOrder32 
*
******************************************************************************/
void AaCpuBitSwapMultiByteOrder32 (u32 * valuePtr, size_t length);


/**
*******************************************************************************
*
*   @brief  Returns 32bit value from given address in reversed byte order
*
*
*   @param[in] valuePtr  Pointer to 32bit unsigned value to convert
*
*   @return Converted value after byte order change
*
*   @par Description:
*   This function changes byte order of given 32bit value (address given).
*   Original value not touched. Converted value is returned.
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
*   #include <IfAaCpu.h>
*
*   u32 result, orig = 0xE550CAFE;
*
*   result = AaCpuBitCopySwapByteOrder32(&orig);
*
*   if ((result != orig) && 
*       (result == 0xFECA50E5) && 
*       (orig == 0xE550CAFE))
*   {
*       // Result value should be converted from original value
*   }
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
*   @see AaCpuBitCopySwapMultiByteOrder32
*
******************************************************************************/
u32 AaCpuBitCopySwapByteOrder32 (u32 * valuePtr);

/**
*******************************************************************************
*
*   @brief  Copies multiple 32bit values to reversed byte order starting from given address
*
*
*   @param[in] srcPtr    Pointer to start of 32bit unsigned values to convert
*   @param[in] dstPtr    Pointer to start of target where to convert
*   @param[in] length    Number of 32bit values to convert
*
*   @return None
*
*   @par Description:
*   This function copies 32bit values to given target area in changed byte
*   order starting from given address until given number of values has been
*   copied (and converted). If #count is set to 0 and/or #srcPtr and/or
*   #dstPtr is set to GLO_NULL, no copy/conversion takes place.
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
*   #include <IfAaCpu.h>
*
*   u32 target[] = {0xaaaaaaaa, 0xbbbbbbbbbb, 0xcccccccccc, 0xdddddddd};
*   u32 orig[] = {0x1, 0x2, 0x3, 0xABBACAFE};
*
*   AaCpuBitCopySwapMultiByteOrder32(orig, target, sizeof(orig) / sizeof(u32));
*
*   // target array should now have following content:
*   // target[0] == 0x01000000;
*   // target[1] == 0x02000000;
*   // target[2] == 0x03000000;
*   // target[3] == 0xFECABAAB;
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
*   @see AaCpuBitCopySwapByteOrder32 
*
******************************************************************************/
void
AaCpuBitCopySwapMultiByteOrder32 (u32 * srcPtr, u32 * dstPtr, size_t length);


/**
*******************************************************************************
*
*   @brief  Changes 64bit value in given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to 64bit unsigned value to convert
*
*   @return Original value before byte order change
*
*   @par Description:
*   This function changes byte order of 64bit value in given address. 
*   Original value is also returned.
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
*   #include <IfAaCpu.h>
*
*   u64 result, value = 0xABBABEEFE550CAFE;
*
*   result = AaCpuBitSwapByteOrder64(&value);
*
*   if ((result != value) && 
*       (result == 0xABBABEEFE550CAFE) && 
*       (value == 0xFECA50E5EFBEBAAB))
*   {
*       // Result value should match to original value
*   }
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
*   @see AaCpuBitSwapMultiByteOrder64
*
******************************************************************************/
u64 AaCpuBitSwapByteOrder64 (u64 * valuePtr);


/**
*******************************************************************************
*
*   @brief  Changes multiple 64bit values starting from given address to reversed byte order
*
*
*   @param[in] valuePtr  Pointer to start of 64bit unsigned values to convert
*   @param[in] length    Number of 64bit values to convert
*
*   @return None
*
*   @par Description:
*   This function changes byte order of 64bit values starting from given address
*   until given number of values has been converted. If #count is set to 0 and/or 
*   #valuePtr is set to GLO_NULL, no byte order conversion takes place.
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
*   #include <IfAaCpu.h>
*
*   u64 values[] = {0x1, 0x2, 0x3, 0xABBACAFEDEADBEEFLLU};
*
*   AaCpuBitSwapMultiByteOrder64(values, sizeof(values) / sizeof(u64));
*
*   // values array should now have following content:
*   // values[0] == 0x0100000000000000LLU;
*   // values[1] == 0x0200000000000000LLU;
*   // values[2] == 0x0300000000000000LLU;
*   // values[3] == 0xEFBEADDEFECABAABLLU;
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
*   @see AaCpuBitSwapByteOrder64 
*
******************************************************************************/
void AaCpuBitSwapMultiByteOrder64 (u64 * valuePtr, size_t length);


/** @} */

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

/*@}*/

#endif /*  _IFAACPU_H */
