/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaCpu service API header file
* @module                AaCpu
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAACPU_H
#define _MCU_RT_IFAACPU_H

#include <CcsCommon.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @defgroup dgAaCpuApiLinux AaCpu LINUX API
 * @ingroup dgAaCpu
 */
/* @{ */
/**
*******************************************************************************
*
*   @brief    Returns frequency of timestamp value in Hz
*
*
*   @param None
*
*   @return 64bit frequency of timebase value in Hz
*
*   @par Description:
*   Timebase value is CPU specific and it frequency can be different between
*   CPUs. This API allows querying the frequency of the timebase so that it is
*   possible to calculate time in standard units. The frequency is returned as
*   hertz.
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
*   double differenceSec;
*   begin = AaCpuTimeBaseGet();
*
*   // Do some things
*
*   end = AaCpuTimeBaseGet();
*   // Calculate how long it took to do some things in timebase units
*   difference = AACPU_TIMEBASE_DIFF_GET(begin, end);
*   // Convert timebase units to standard time units (secs)
*   differenceSec = (double)difference / (double)AaCpuTimeBaseFreqGet();
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
*   @see AACPU_TIMEBASE_DIFF_GET
*
******************************************************************************/
u64 AaCpuTimeBaseFreqGet (void);

/**
*******************************************************************************
*
*   @brief    Opens access to kernel trace file
*
*
*   @param None
*
*   @return 0 in case no errors, negative value in case of errors
*
*   @par Description:
*   In order to add markers to Linux kernel trace file using AaCpuKernelTraceMark(),
*   access to it must be open by this function. It is needed to be called only
*   once in EE context. Subsequent calls will be ignored.
*
*   @par Errors:
*   In case of problems with access to Linux kernel trace file (Linux kernel trace
*   subsystem is not enabled) function reports error message on stderr and returns -1.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see AaCpuKernelTraceMark
*
******************************************************************************/
i32 AaCpuKernelTraceMarkerOpen(void);

/**
*******************************************************************************
*
*   @brief    Formats and adds given trace marker to kernel trace file
*
*
*   @param fmt  printf style formatting string
*
*   @return 0 in case no errors, negative value in case of errors
*
*   @par Description:
*   This function can be used to add trace marker to Linux kernel trace file after
*   access to it has been opened using AaCpuKernelTraceMarkerOpen(). Given trace
*   marker is formatted as printf-style. Linux kernel trace subsystem must be
*   enabled first by writing 'echo 1 > /sys/kernel/debug/tracing/tracing_on'.
*   There is no API at the moment to do that from SW.
*
*   @par Errors:
*   In case Linux kernel trace subsystem is not enabled, function will return -1.
*
*   @par Restrictions:
*   Linux kernel trace subsystem must be enabled, otherwise this call may fail.
*
*   @par Example:
*   @code
*       #include <IfAaCpu.h>
*
*       int rc;
*       rc = AaCpuKernelTraceMarkerOpen();
*
*       if (rc != 0)
*          ... handle error ...
*
*       rc = AaCpuKernelTraceMark("my kernel trace marker %i %s", 1000, "string");
*
*       if (rc != 0)
*          ... handle error ...*
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
*   @see AaCpuKernelTraceMarkerOpen
*
******************************************************************************/
i32 AaCpuKernelTraceMark(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

/**
*******************************************************************************
*
*   @brief    Copies Linux kernel trace files to given destination path
*
*
*   @param destinationPath  Destination for the trace files
*
*   @return 0 in case no errors, any other value (negative or positive) in case of error
*
*   @par Description:
*   This function copies Linux kernel trace files (global and core specific) to
*   given destination directory. The destination directory must exist.
*
*   @par Errors:
*   In case Linux kernel trace subsystem is not enabled or destination directory
*   does not exist, function returns negative value.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see AaCpuKernelTraceMark
*
******************************************************************************/
i32 AaCpuKernelTraceFlushCoreSpecificsToFiles(const char *destinationPath);


/** @brief Static initializer for 32bit atomic
*
*   @param[in] __initVal  Initialization value*
*   @par Description:
*   This macro can be used instead of AaCpuAtomicSet32().
*
*   @par Example:
*   @code
*     #include <IfAaCpu.h>
*
*     TAaCpuAtomic32 var = AACPU_ATOMIC_STATIC_INIT32(-3487);
*   @endcode
*
*   @note This is a macro for C99 compatible compilers (also for GCC) and
*         inline function for older C90 compilers.
*/
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && __GNUC__
# define AACPU_ATOMIC_STATIC_INIT32(__initVal) (TAaCpuAtomic32){ (__initVal) }
#else
static __CCS_INLINE__ TAaCpuAtomic32 AACPU_ATOMIC_STATIC_INIT32 (i32 initVal)
{
    TAaCpuAtomic32 atomic;
    atomic.data = initVal;
    return atomic;
}                               /* AACPU_ATOMIC_STATIC_INIT32 */
#endif


/** @name Atomic 64 bit API
* @{
*/

/** @brief Static initializer for 64bit atomic
*
*   @param[in] __initVal  Initialization value
*
*   @par Description:
*   This macro can be used instead of AaCpuAtomicSet64().
*
*   @par Example:
*   @code
*     #include <IfAaCpu.h>
*
*     TAaCpuAtomic64 var = AACPU_ATOMIC_STATIC_INIT64(-3487);
*   @endcode
*
*   @note This is a macro for C99 compatible compilers (also for GCC) and
*         inline function for older C90 compilers.
*/
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && __GNUC__
# define AACPU_ATOMIC_STATIC_INIT64(__initVal) (TAaCpuAtomic64){ AACPU_SPINLOCK_STATIC_INIT(), (__initVal) }
#else
static __CCS_INLINE__ TAaCpuAtomic64 AACPU_ATOMIC_STATIC_INIT64 (i64 initVal)
{
    TAaCpuAtomic64 atomic;
    atomic.data = initVal;
    return atomic;
}                               /* AACPU_ATOMIC_STATIC_INIT64 */
#endif



/** @brief Static initializer for spinlock
*
*   @par Description:
*   This macro can be used instead of AaCpuSpinLockInit().
*
*   @par Example:
*   @code
*     #include <IfAaCpu.h>
*
*     TAaCpuSpinLock spinlock = AACPU_SPINLOCK_STATIC_INIT();
*   @endcode
*
*   @note This is a macro for C99 compatible compilers (also for GCC) and
*         inline function for older C90 compilers.
*/
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && __GNUC__
# define AACPU_SPINLOCK_STATIC_INIT() (TAaCpuSpinLock){ AACPU_SPINLOCK_INIT, \
                                                        AACPU_SPINLOCK_MAX_SPINS, \
                                                        AACPU_SPINLOCK_MAX_YIELDS }
#else
static __CCS_INLINE__ TAaCpuSpinLock AACPU_SPINLOCK_STATIC_INIT (void)
{
    TAaCpuSpinLock lock;
    lock.value = AACPU_SPINLOCK_INIT;
    lock.spinThold = AACPU_SPINLOCK_MAX_SPINS;
    lock.yieldThold = AACPU_SPINLOCK_MAX_YIELDS;

    return lock;
}                               /* AACPU_SPINLOCK_STATIC_INIT */
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

/*@}*/

#endif /*  _MCU_RT_IFAACPU_H */
